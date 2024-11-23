#include "GridCell.h"

void UGridCell::Initialize(const FVector2D GridPosition, float CellSize)
{
	Cell.Position = GridPosition;
	Cell.Size = CellSize;
}

FRect UGridCell::GridCell() const
{
	return Cell;
}

FVector2D UGridCell::CenterPosition() const
{
	// Cell position is bottom left
	const float HalfSize{Cell.Size / 2};
	return FVector2D{Cell.Position.X + HalfSize, Cell.Position.Y + HalfSize};
}

void UGridCell::DrawDebugCell(uint32 Index) const
{
	const FVector Start{Cell.Position, 0.f};
	const FVector Top{Cell.Position.X, Cell.Position.Y + Cell.Size, 0.f};
	const FVector Right{Cell.Position.X + Cell.Size, Cell.Position.Y, 0.f};
	DrawDebugLine(GetWorld(), Start, Top, FColor::Red, true);
	DrawDebugLine(GetWorld(), Start, Right, FColor::Red, true);

	DrawDebugString(GetWorld(), FVector{CenterPosition(), 0.f}, FString::Printf(TEXT("%d"), Index), nullptr, FColor::Red, 1000);
}
