#include "BaseEntity.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseEntity::ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	PreyCapsule = CreateDefaultSubobject<UCapsuleComponent>("Forward Arrow");
	PreyCapsule->SetupAttachment(RootComponent);

	// Setup Movement
	UCharacterMovementComponent* CharacterMovementComponent{GetCharacterMovement()};
	CharacterMovementComponent->MaxWalkSpeed = MaxSpeed;
	CharacterMovementComponent->MaxAcceleration = Acceleration;
	CharacterMovementComponent->bOrientRotationToMovement = true;
}

void ABaseEntity::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
