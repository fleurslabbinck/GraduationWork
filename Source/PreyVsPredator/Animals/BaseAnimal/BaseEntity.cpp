#include "BaseEntity.h"

#include "PreyVsPredator/Animals/Flocking/BaseFlock.h"
#include "PreyVsPredator/Animals/Flocking/FlockSubsystem.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PreyVsPredator/Animals/Widgets/EntityStats.h"


ABaseEntity::ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	EntityCapsule = CreateDefaultSubobject<UCapsuleComponent>("Entity Capsule");
	EntityCapsule->SetupAttachment(RootComponent);
	EntityCapsule->SetGenerateOverlapEvents(true);
	EntityCapsule->SetCollisionProfileName(PreyVsPredator::CollisionPresets::AnimalCollision);

	PerceptionSphere = CreateDefaultSubobject<USphereComponent>("Perception Sphere");
	PerceptionSphere->SetupAttachment(RootComponent);
	PerceptionSphere->SetGenerateOverlapEvents(true);
	PerceptionSphere->SetCollisionProfileName(PreyVsPredator::CollisionPresets::AnimalPerception);

	EntityStats = CreateDefaultSubobject<UWidgetComponent>("Entity Stats");
	EntityStats->SetupAttachment(RootComponent);
	EntityStats->SetDrawAtDesiredSize(true);
	
	// Setup Movement
	UCharacterMovementComponent* CharacterMovementComponent{GetCharacterMovement()};
	CharacterMovementComponent->MaxAcceleration = Acceleration;
	CharacterMovementComponent->bOrientRotationToMovement = true;
}

void ABaseEntity::BeginPlay()
{
	Super::BeginPlay();

	// Set radius of perception sphere
	PerceptionSphere->SetSphereRadius(PerceptionRadius);
	PerceptionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseEntity::OnPerceptionBegin);
	PerceptionSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseEntity::OnPerceptionEnd);

	InitializeStats();
	InitializeFlock();
}

void ABaseEntity::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateWidgetRotation();
}

void ABaseEntity::OnPerceptionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent == nullptr || OverlappedComponent == EntityCapsule) return;

	// Check if other entity has same tag
	if (OtherActor->ActorHasTag(EntityTag))
	{
		ABaseEntity* OtherEntity{Cast<ABaseEntity>(OtherActor)};
		if (OtherEntity == nullptr) return;
		
		HandleFlock(OtherEntity);
	}
}

void ABaseEntity::OnPerceptionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if other entity has same tag
	if (OtherActor->ActorHasTag(EntityTag))
	{
		HandleFlockOutOfReach();
	}
}

#pragma region Stats
void ABaseEntity::InitializeStats()
{
	if (UUserWidget* Widget{Cast<UUserWidget>(EntityStats->GetWidget())}; Widget != nullptr)
	{
		m_EntityStatsWidget = Cast<UEntityStats>(Widget);
		if (m_EntityStatsWidget != nullptr)
		{
			m_EntityStatsWidget->UpdateStatsBar(EStatsBarType::Stamina, m_CurrentStamina);
			m_EntityStatsWidget->UpdateStatsBar(EStatsBarType::Health, m_CurrentHealth);
			m_EntityStatsWidget->UpdateStatsBar(EStatsBarType::Hunger, m_CurrentHunger);
			m_EntityStatsWidget->UpdateStatsBar(EStatsBarType::Thirst, m_CurrentThirst);
		}
	}
	
	SetupStatsTimer();
}

void ABaseEntity::SetupStatsTimer()
{
	// Setup timer to start updating stats
	GetWorld()->GetTimerManager().SetTimer(m_StatsTimer, this, &ABaseEntity::UpdateStats, StatsUpdateRate, true);
}

void ABaseEntity::UpdateWidgetRotation()
{
	// Stats always face camera
	const FVector CameraLocation{UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation()};
	const FVector ToCamera{CameraLocation - EntityStats->GetComponentLocation()};
	const FRotator LookAtRotation{FRotationMatrix::MakeFromX(ToCamera).Rotator()};
	EntityStats->SetWorldRotation(LookAtRotation);
}

void ABaseEntity::UpdateStats()
{
	bool UpdateHealth{false};
	
	if (m_CurrentHunger >= LowFoodThresshold && m_CurrentThirst >= LowWaterThresshold)
	{
		// Increase health if not hungry or thirsty
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth + HealthIncreaseRate, 0, m_MaxStats);
		UpdateHealth = true;
	}
	else if (m_CurrentHunger < LowFoodThresshold || m_CurrentThirst < LowWaterThresshold)
	{
		// Decrease health if starving or dehydrated
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth - HealthDecreaseRate, 0, m_MaxStats);
		UpdateHealth = true;
	}

	if (UpdateHealth)
	{
		// Update health bar
		m_EntityStatsWidget->UpdateStatsBar(EStatsBarType::Health, m_CurrentHealth);
	}
	
	m_CurrentHunger = FMath::Clamp(m_CurrentHunger - FoodDecreaseRate, 0, m_MaxStats);
	m_CurrentThirst = FMath::Clamp(m_CurrentThirst - WaterDecreaseRate, 0, m_MaxStats);

	// Update hunger and thirst bars
	m_EntityStatsWidget->UpdateStatsBar(EStatsBarType::Hunger, m_CurrentHunger);
	m_EntityStatsWidget->UpdateStatsBar(EStatsBarType::Thirst, m_CurrentThirst);

	// Check if entity thirsty
	if (m_CurrentThirst < LowWaterThresshold && m_CurrentThirst < m_CurrentHunger)
	{
		if (m_Flock != nullptr)
		{
			m_Flock->SetThirsty(true);
		}
	}
}

bool ABaseEntity::LowHealth() const
{
	return m_CurrentHealth < LowHealthThresshold;
}

bool ABaseEntity::Hungry() const
{
	return m_CurrentHunger < LowFoodThresshold;
}

bool ABaseEntity::Thirsty() const
{
	return m_CurrentThirst < LowWaterThresshold;
}

void ABaseEntity::Consume(EWorldCellType Type)
{
	switch (Type)
	{
	case EWorldCellType::Grass:
	case EWorldCellType::Carcass:
		m_CurrentHunger = FMath::Clamp(m_CurrentHunger + FoodIncreaseRate, 0, m_MaxStats);
		break;
	case EWorldCellType::Water:
		m_CurrentThirst = FMath::Clamp(m_CurrentThirst + WaterIncreaseRate, 0, m_MaxStats);
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region Flocking
void ABaseEntity::InitializeFlock()
{
	TArray<AActor*> OverlappingEntities{};
	PerceptionSphere->GetOverlappingActors(OverlappingEntities);

	if (m_Flock != nullptr) return;
	
	// Create flock
	ABaseFlock* Flock{GetWorld()->GetSubsystem<UFlockSubsystem>()->CreateFlock()};

	for (AActor* EntityActor : OverlappingEntities)
	{
		if (!EntityActor->ActorHasTag(EntityTag)) break;

		ABaseEntity* Entity{Cast<ABaseEntity>(EntityActor)};
		if (Entity != nullptr)
		{
			Flock->AddEntity(Entity);
		}
	}

	GetWorld()->GetSubsystem<UFlockSubsystem>()->UpdateFlocks();
}

void ABaseEntity::HandleFlock(ABaseEntity* OtherEntity)
{
	// If entity does not have a flock
	if (m_Flock == nullptr)
	{
		// Handle both entities not having a flock
		if (OtherEntity->Flock() == nullptr)
		{
			ABaseFlock* Flock{GetWorld()->GetSubsystem<UFlockSubsystem>()->CreateFlock()};
			Flock->AddEntity(this);
			Flock->AddEntity(OtherEntity);
		}
		// Handle other entity having a flock
		else
		{
			OtherEntity->Flock()->AddEntity(this);
		}
	}
	// If entity does have a flock
	else
	{
		// Handle other entity not having a flock
		if (OtherEntity->Flock() == nullptr)
		{
			m_Flock->AddEntity(OtherEntity);
		}
		// Handle both entities having a different flock
		else if (OtherEntity->Flock() != m_Flock)
		{
			// Merge flocks
			GetWorld()->GetSubsystem<UFlockSubsystem>()->MergeFlocks(m_Flock, OtherEntity->Flock());
		}
	}
}

void ABaseEntity::HandleFlockOutOfReach()
{
	TArray<AActor*> OverlappingEntities{};
	PerceptionSphere->GetOverlappingActors(OverlappingEntities);

	if (OverlappingEntities.Num() > 1) return;
	
	// Set bool to transition to flocking state if in grazing state
	m_ShouldFlock = true;

	GetWorld()->GetTimerManager().SetTimer(m_FlockResetTimer, this, &ABaseEntity::ResetFlockTimer, FlockResetTime);
}

bool ABaseEntity::ShouldFlock() const
{
	return m_ShouldFlock;
}

void ABaseEntity::ResetFlockTimer()
{
	// Set flock to nullptr, will be set again if in flocking state
	m_Flock->RemoveEntity(this);
	GetWorld()->GetSubsystem<UFlockSubsystem>()->UpdateFlocks();
	
	m_ShouldFlock = false;
	
	// Reset timer in case we get here earlier
	GetWorld()->GetTimerManager().ClearTimer(m_FlockResetTimer);
}

void ABaseEntity::SetFlock(ABaseFlock* NewFlock)
{
	m_Flock = NewFlock;
}

ABaseFlock* ABaseEntity::Flock() const
{
	return m_Flock;
}
#pragma endregion