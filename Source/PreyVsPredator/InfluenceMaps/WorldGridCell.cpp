#include "WorldGridCell.h"


void UWorldGridCell::ChangeWorldType(EWorldCellType NewType)
{
	Type = NewType;
}

EWorldCellType UWorldGridCell::WorldType() const
{
	return Type;
}

bool UWorldGridCell::Occupied() const
{
	return bOccupied;
}

void UWorldGridCell::Occupy()
{
	bOccupied = true;
}

float UWorldGridCell::Content() const
{
	return m_Content;
}

void UWorldGridCell::Consume()
{
	SetContents(ConsumeRate);
}

void UWorldGridCell::Regenerate()
{
	SetContents(RegenRate);
}

void UWorldGridCell::SetContents(float Rate)
{
	m_Content = FMath::Clamp(m_Content + Rate, 0, MaxContent);
}