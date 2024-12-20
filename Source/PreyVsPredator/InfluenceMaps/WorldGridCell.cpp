#include "WorldGridCell.h"

#include "Engine/StaticMeshActor.h"


void UWorldGridCell::Initialize(const FVector GridPosition, float CellSize)
{
	Super::Initialize(GridPosition, CellSize);

	// Set cell pos
	const FVector Pos{CenterPosition()};
	m_StaticMesh = Cast<AStaticMeshActor>(GetWorld()->SpawnActor(AStaticMeshActor::StaticClass(), &Pos));

	// Scale to grid size
	const float Scale{CellSize / MeshScale};
	m_StaticMesh->SetActorScale3D({Scale, Scale, Scale});
	
	// Assign the static mesh to the component
	m_StaticMesh->GetStaticMeshComponent()->SetStaticMesh(GridCellMesh);

	// Create a dynamic material instance based on the material of the static mesh
	if (UMaterialInterface* BaseMaterial{GridCellMesh->GetMaterial(0)}; BaseMaterial != nullptr)
	{
		m_CellMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		if (m_CellMaterial != nullptr)
		{
			// Assign the dynamic material to the mesh component
			m_StaticMesh->GetStaticMeshComponent()->SetMaterial(0, m_CellMaterial);
		}
	}

	SetCellColor(GrassColor);
}

void UWorldGridCell::ChangeWorldType(EWorldCellType NewType)
{
	Type = NewType;
	FLinearColor Color;

	switch (Type)
	{
	case EWorldCellType::Grass:
		Color = GrassColor;
		break;
	case EWorldCellType::Water:
		Color = WaterColor;
		break;
	default:
		return;
	}

	SetCellColor(Color);
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

void UWorldGridCell::SetCellColor(FLinearColor NewColor) const
{
	m_CellMaterial->SetVectorParameterValue(CellColorParameter, NewColor);
}

void UWorldGridCell::SetContents(float Rate)
{
	if (Type != EWorldCellType::Grass) return;

	// Set new content value
	m_Content = FMath::Clamp(m_Content + Rate, 0, MaxContent);

	// Set new color depending on content value
	SetCellColor(FMath::Lerp(DirtColor, GrassColor, m_Content));
}
