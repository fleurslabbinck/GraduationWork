#pragma once

#include "CoreMinimal.h"
#include "WorldGridCell.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldGridSubsystem.generated.h"


class UGridCell;
class UGrid;

UCLASS()
class PREYVSPREDATOR_API UWorldGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Grid")
	FVector StartPosition{};

	UPROPERTY(EditAnywhere, Category="Grid")
	uint32 Rows{50};

	UPROPERTY(EditAnywhere, Category="Grid")
	uint32 Columns{50};

	UPROPERTY(EditAnywhere, Category="Grid")
	float CellSize{150.f};

	UPROPERTY(EditAnywhere, Category="Grid")
	float AcceptanceDivisionFactor{3.f};

public:
	void SetupGrid(TSubclassOf<UWorldGridCell> WorldGridCellClass);

	float AcceptanceRadius() const;
	FVector NextCellPosition(const FVector& CurrentPosition, EWorldCellType Type) const;
	bool AttemptConsumption(const FVector& CurrentPosition, EWorldCellType Type) const;
	UWorldGridCell* CellAtPosition(const FVector& Pos) const;

private:
	UPROPERTY()
	UGrid* m_WorldGrid{nullptr};

	void MakePond(uint32 Index) const;
};
