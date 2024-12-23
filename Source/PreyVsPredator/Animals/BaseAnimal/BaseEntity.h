﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEntity.generated.h"

class USphereComponent;
class ABaseFlock;
class UBehaviorTree;
class UArrowComponent;
class UCapsuleComponent;

namespace PreyVsPredator::CollisionPresets
{
	const FName AnimalCollision{TEXT("AnimalCollision")};
	const FName AnimalPerception{TEXT("AnimalPerception")};
}

UCLASS()
class PREYVSPREDATOR_API ABaseEntity : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Instanced, Category="Components")
	UCapsuleComponent* EntityCapsule;

	UPROPERTY(EditDefaultsOnly, Instanced, Category="Components")
	USphereComponent* PerceptionSphere;

	UPROPERTY(EditAnywhere, Category="Entity|Perception")
	float PerceptionRadius{1000.f};

	UPROPERTY(EditAnywhere, Category="Entity|Movement")
	float MaxSpeed{600.f};

	UPROPERTY(EditAnywhere, Category="Entity|Movement")
	float Acceleration{1500.f};

	UPROPERTY(EditAnywhere, Category="Entity|Tag")
	FName EntityTag{"Prey"};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float LowHealthThresshold{20.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float LowFoodThresshold{20.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float FoodDecreaseRate{1.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float LowWaterThresshold{20.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float WaterDecreaseRate{0.7f};
	
	UPROPERTY(EditAnywhere, Category="Entity|Flock")
	uint32 MinFlockAmount{2};

	UPROPERTY(EditAnywhere, Category="Entity|Flock")
	float FlockResetTime{5.f};

public:
	ABaseEntity();

	bool LowHealth() const;
	bool Hungry() const;
	bool Thirsty() const;
	
	bool ShouldFlock() const;
	void ResetFlockTimer();
	
	void SetFlock(ABaseFlock* NewFlock);
	ABaseFlock* Flock() const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool m_ShouldFlock{false};
	const float m_MaxStats{100.f};
	float m_CurrentHealth{m_MaxStats};
	float m_CurrentHunger{m_MaxStats};
	float m_CurrentThirst{m_MaxStats};
	FTimerHandle m_FlockResetTimer{};

	UPROPERTY()
	ABaseFlock* m_Flock{nullptr};

	UFUNCTION()
	void OnPerceptionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPerceptionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void InitializeFlock();
	void HandleFlock(ABaseEntity* OtherEntity);
	void HandleFlockOutOfReach();
};