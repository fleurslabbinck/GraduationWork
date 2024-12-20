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

	uint32 TotalCells() const;
	UGridCell* CurrentGridCell(const FVector& CurrentPosition) const;
	UGridCell* NextGridCell(const FVector& CurrentPosition, EWorldCellType Type = EWorldCellType::None) const;
	UGridCell* GridCellAtIndex(uint32 Index) const;

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
	
	FVector2D PositionFromIndex(uint32 Index) const;
	uint32 IndexFromPosition(const FVector2D& Position) const;
	
	uint32 ClosestCell(const FVector2D& Position, EWorldCellType Type) const;
	void ValidNeighbors(TArray<uint32>& NeighborsArr, const FVector2D& Position, uint32 Index, EWorldCellType Type) const;
	bool IsCellTypeValid(uint32 Index, EWorldCellType Type) const;
};
