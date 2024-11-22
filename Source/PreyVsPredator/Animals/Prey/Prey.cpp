#include "Prey.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


APrey::APrey()
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

void APrey::BeginPlay()
{
	Super::BeginPlay();
}

void APrey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
