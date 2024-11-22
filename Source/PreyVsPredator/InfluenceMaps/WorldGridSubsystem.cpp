#include "WorldGridSubsystem.h"

void UWorldGridSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FVector2D Pos{};

	for (int32 Row{}; Row < Rows; ++Row)
	{
		for (int32 Col{}; Col < Columns; ++Col)
		{
			Pos = FVector2D{Row * CellSize, Col * CellSize};
			const FWorldCell Cell{Pos};
			WorldGrid[Row][Col] = Cell;
		}
	}
}

void UWorldGridSubsystem::Deinitialize()
{
	Super::Deinitialize();

	WorldGrid.Empty();
}
