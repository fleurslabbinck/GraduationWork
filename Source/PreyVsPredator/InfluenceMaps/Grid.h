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
	UGrid();

	void SetCellClass(const TSubclassOf<UGridCell> CellClass);
	void Initialize(const FVector& GridPosition, uint8 GridRows, uint8 GridColumns, float CellSize);

	UGridCell* NextGridCell(const FVector& CurrentPosition) const;

private:
	uint32 m_Rows{};
	uint32 m_Columns{};
	uint32 m_CellSize{};
	TArray<FIntPoint> m_GridDirections;
	TSubclassOf<UGridCell> m_GridCellClass{UGridCell::StaticClass()};
	
	UPROPERTY()
	TArray<UGridCell*> m_GridCells;

	uint32 CalculateIndex(uint32 Row, uint32 Column) const;
	uint32 RowFromIndex(uint32 Index) const;
	uint32 ColumnFromIndex(uint32 Index) const;
	
	FVector PositionFromIndex(uint32 Index) const;
	uint32 IndexFromPosition(const FVector2D& Position) const;
	
	uint32 ClosestCell(const FVector2D& Position) const;
	TArray<uint32> ValidNeighbors(uint32 Index) const;
};
