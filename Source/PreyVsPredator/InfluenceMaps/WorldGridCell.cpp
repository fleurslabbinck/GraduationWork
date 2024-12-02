#include "WorldGridCell.h"


void UWorldGridCell::ChangeWorldType(EWorldCellType NewType)
{
	Type = NewType;
}

EWorldCellType UWorldGridCell::WorldType() const
{
	return Type;
}

float UWorldGridCell::Content() const
{
	return m_Content;
}

bool UWorldGridCell::Consume()
{
	const bool bHasContent{m_Content > 0};
	
	if (bHasContent)
	{
		SetContents(ConsumeRate);
	}
	
	return Available();
}

void UWorldGridCell::Regenerate()
{
	SetContents(RegenRate);
}

void UWorldGridCell::SetContents(float Rate)
{
	m_Content = FMath::Clamp(m_Content + Rate, 0, MaxContent);

	if (m_Content <= 0)
	{
		SetAvailability(false);
	}

	if (!Available() && m_Content >= 1)
	{
		SetAvailability(true);
	}
}