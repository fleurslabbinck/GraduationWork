#include "BaseEntity.h"

#include "BaseFlock.h"
#include "FlockSubsystem.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


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
	
	// Setup Movement
	UCharacterMovementComponent* CharacterMovementComponent{GetCharacterMovement()};
	CharacterMovementComponent->MaxWalkSpeed = MaxSpeed;
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

	InitializeFlock();
}

void ABaseEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

#pragma region Flocking
void ABaseEntity::OnPerceptionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent == nullptr || OverlappedComponent == EntityCapsule) return;

	// Check if other entity has appropriate tag
	if (OtherActor->ActorHasTag(EntityTag))
	{
		ABaseEntity* OtherEntity{Cast<ABaseEntity>(OtherActor)};
		if (OtherEntity == nullptr) return;
		
		HandleFlock(OtherEntity);
	}
}

void ABaseEntity::OnPerceptionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(EntityTag))
	{
		HandleFlockOutOfReach();
	}
}

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