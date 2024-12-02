#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Prey.generated.h"

class UBehaviorTree;
class UArrowComponent;
class UCapsuleComponent;

UCLASS()
class PREYVSPREDATOR_API APrey : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Instanced, Category="Components")
	UCapsuleComponent* PreyCapsule;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MaxSpeed{600.f};

	UPROPERTY(EditAnywhere, Category="Movement")
	float Acceleration{1500.f};

public:
	APrey();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
