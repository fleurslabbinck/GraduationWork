﻿#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

UCLASS()
class PREYVSPREDATOR_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	bool Dead{false};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float Direction{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float Speed{};

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void SetDead();
};
