#include "GridCell.h"

void UGridCell::Initialize(const FVector GridPosition, float CellSize)
{
	Cell.Position = GridPosition;
	Cell.Size = CellSize;
}

FRect UGridCell::GridCell() const
{
	return Cell;
}

FVector UGridCell::CenterPosition() const
{
	// Cell position is bottom left
	const float HalfSize{Cell.Size / 2};
	return FVector{Cell.Position.X + HalfSize, Cell.Position.Y + HalfSize, Cell.Position.Z};
}

bool UGridCell::Available() const
{
	return bAvailable;
}

void UGridCell::SetAvailability(bool Available)
{
	bAvailable = Available;
}

void UGridCell::DrawDebugCell(uint32 Index) const
{
	const FVector Start{Cell.Position};
	const FVector Top{Cell.Position.X, Cell.Position.Y + Cell.Size, Cell.Position.Z};
	const FVector Right{Cell.Position.X + Cell.Size, Cell.Position.Y, Cell.Position.Z};
	DrawDebugLine(GetWorld(), Start, Top, FColor::Red, true);
	DrawDebugLine(GetWorld(), Start, Right, FColor::Red, true);

	DrawDebugString(GetWorld(), FVector{CenterPosition()}, FString::Printf(TEXT("%d"), Index), nullptr, FColor::Red, 1000);
}
