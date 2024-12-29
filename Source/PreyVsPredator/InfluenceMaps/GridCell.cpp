#include "GridCell.h"

void UGridCell::Initialize(const FVector GridPosition, float CellSize)
{
	m_Cell.Position = GridPosition;
	m_Cell.Size = CellSize;
}

FRect UGridCell::GridCell() const
{
	return m_Cell;
}

FVector UGridCell::CenterPosition() const
{
	// Cell position is bottom left
	const float HalfSize{m_Cell.Size / 2};
	return FVector{m_Cell.Position.X + HalfSize, m_Cell.Position.Y + HalfSize, m_Cell.Position.Z};
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
	const FVector Start{m_Cell.Position};
	const FVector Top{m_Cell.Position.X, m_Cell.Position.Y + m_Cell.Size, m_Cell.Position.Z};
	const FVector Right{m_Cell.Position.X + m_Cell.Size, m_Cell.Position.Y, m_Cell.Position.Z};
	DrawDebugLine(GetWorld(), Start, Top, FColor::Red, true);
	DrawDebugLine(GetWorld(), Start, Right, FColor::Red, true);
}
