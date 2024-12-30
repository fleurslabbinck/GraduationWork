#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PreyVsPredator/Helpers/GridData.h"
#include "BaseEntity.generated.h"

class UEntityStats;
class UWidgetComponent;
class USphereComponent;
class ABaseFlock;
class UBehaviorTree;
class UArrowComponent;
class UCapsuleComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

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

	UPROPERTY(EditDefaultsOnly, Instanced, Category="Components")
	UWidgetComponent* EntityStats;

	UPROPERTY(EditAnywhere, Category="Entity|Movement")
	float Acceleration{1500.f};

	UPROPERTY(EditAnywhere, Category="Entity|Perception")
	float PerceptionRadius{1000.f};

	UPROPERTY(EditAnywhere, Category="Entity|Tag")
	FName EntityTag{"Prey"};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float StatsUpdateRate{1.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float LowHealthThresshold{20.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float HealthIncreaseRate{8.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float HealthDecreaseRate{5.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float LowFoodThresshold{20.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float FoodIncreaseRate{10.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float FoodDecreaseRate{2.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float LowWaterThresshold{20.f};
	
	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float WaterIncreaseRate{20.f};

	UPROPERTY(EditAnywhere, Category="Entity|Stats")
	float WaterDecreaseRate{1.f};
	
	UPROPERTY(EditAnywhere, Category="Entity|Flock")
	uint32 MinFlockAmount{2};

	UPROPERTY(EditAnywhere, Category="Entity|Flock")
	float FlockResetTime{5.f};

public:
	ABaseEntity();

	bool Dead() const;
	bool Hungry() const;
	bool Thirsty() const;
	bool FullWater() const;

	void Consume(EWorldCellType Type);
	
	bool ShouldFlock() const;
	void ResetFlockTimer();
	
	void SetFlock(ABaseFlock* NewFlock);
	ABaseFlock* Flock() const;

	FOnDeath OnDeath;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	bool m_ShouldFlock{false};
	const float m_MaxStats{100.f};
	float m_CurrentStamina{m_MaxStats};
	float m_CurrentHealth{m_MaxStats};
	float m_CurrentFood{m_MaxStats};
	float m_CurrentWater{};
	FTimerHandle m_StatsTimer{};
	FTimerHandle m_FlockResetTimer{};

	UPROPERTY()
	ABaseFlock* m_Flock{nullptr};

	UPROPERTY()
	UEntityStats* m_EntityStatsWidget{nullptr};

	UFUNCTION()
	void OnPerceptionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPerceptionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void InitializeStats();
	void SetupStatsTimer();
	void UpdateWidgetRotation();
	void UpdateStats();
	void UpdateHealth();
	void UpdateFood();
	void UpdateWater();

	void InitializeFlock();
	void HandleFlock(ABaseEntity* OtherEntity);
	void HandleFlockOutOfReach();
};
