#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PreyVsPredator/Helpers/SimulationData.h"
#include "PreyVsPredatorGameModeBase.generated.h"

class APBTController;
class AHFSMBTHController;
class ABaseEntity;
class UWorldGridCell;
class UGrid;

UCLASS()
class PREYVSPREDATOR_API APreyVsPredatorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="PreyVsPredator|Grid")
	TSubclassOf<UWorldGridCell> WorldGridCellClass;

	UPROPERTY(EditAnywhere, Category="PreyVsPredator|Simulation")
	ESimulationMethod SimulationMethod{ESimulationMethod::HFSMBTH};

	UPROPERTY(EditAnywhere, Category="PreyVsPredator|Entities")
	TSubclassOf<ABaseEntity> PreyClass;

	UPROPERTY(EditAnywhere, Category="PreyVsPredator|Entities")
	TSubclassOf<AHFSMBTHController> HFSMBTHPreyControllerClass;

	UPROPERTY(EditAnywhere, Category="PreyVsPredator|Entities")
	TSubclassOf<APBTController> PBTPreyControllerClass;

	UPROPERTY(EditAnywhere, Category="PreyVsPredator|Entities")
	uint32 MaxAmountPrey{20};

	UPROPERTY(EditAnywhere, Category="Grid")
	uint8 PondSize{3};

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SpawnEntity();
};
