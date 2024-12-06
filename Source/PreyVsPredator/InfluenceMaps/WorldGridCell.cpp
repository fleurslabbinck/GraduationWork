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
	if (m_Content > FLT_EPSILON)
	{
		float Rate;
		
		switch (Type)
		{
		case EWorldCellType::Grass:
			Rate = ConsumeRate;
			break;
		default:
			Rate = 0;
			break;
		}
		
		SetContents(Rate);

		// Cell becomes unavailable and starts regenerating when no more content
		if (m_Content < FLT_EPSILON)
		{
			SetAvailability(false);
			Regenerate();
		}
	}
	
	return Available();
}

void UWorldGridCell::Regenerate()
{
	SetContents(RegenRate);

	// Regenerate as long as cell is not available and content not full
	if (!Available() && m_Content < 1.f)
	{
		GetWorld()->GetTimerManager().SetTimer(m_RegenTimer, this, &UWorldGridCell::Regenerate, RegenTime);
	}
	else
	{
		SetAvailability(true);
	}
}

void UWorldGridCell::SetContents(float Rate)
{
	m_Content = FMath::Clamp(m_Content + Rate, 0, MaxContent);
}