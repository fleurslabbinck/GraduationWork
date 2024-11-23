#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "UObject/Object.h"
#include "Grid.generated.h"


class UGridCell;

UCLASS()
class PREYVSPREDATOR_API UGrid : public UObject
{
	GENERATED_BODY()

public:
	UGrid() = default;

	void SetCellClass(const TSubclassOf<UGridCell> CellClass);
	void Initialize(const FVector2D& GridPosition, uint8 GridRows, uint8 GridColumns, float CellSize);

	

private:
	uint32 m_Rows{};
	uint32 m_Columns{};
	uint32 m_CellSize{};
	
	TSubclassOf<UGridCell> m_GridCellClass{UGridCell::StaticClass()};
	
	UPROPERTY()
	TArray<UGridCell*> m_GridCells;

	FVector2D PositionFromIndex(uint32 Index) const;
	uint32 IndexFromPosition(FVector2D Position) const;
};
