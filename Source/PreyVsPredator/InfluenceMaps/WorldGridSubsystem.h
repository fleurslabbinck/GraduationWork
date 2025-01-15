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

public:
	void SetPondSize(uint8 NewPondSize);
	void SetupGrid(TSubclassOf<UWorldGridCell> WorldGridCellClass, const FVector& StartPosition, uint32 Rows, uint32 Columns, float CellSize);

	bool AttemptConsumption(const FVector& CurrentPosition, EWorldCellType Type) const;
	float AcceptanceRadius() const;
	FVector RandomPositionInGrid() const;
	FVector NextCellPosition(const FVector& CurrentPosition, EWorldCellType Type) const;
	UWorldGridCell* CellAtPosition(const FVector& Pos) const;

private:
	uint8 m_PondSize{};
	uint32 m_Rows{};
	uint32 m_Columns{};
	float m_CellSize{};
	float m_AcceptanceDivisionFactor{3.f};
	
	UPROPERTY()
	UGrid* m_WorldGrid{nullptr};

	void ChangeToWater(uint32 Index) const;
	void MakePond(uint16 StartRow, uint16 StartCol) const;
};
