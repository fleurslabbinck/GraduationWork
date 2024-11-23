#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "UObject/Object.h"
#include "WorldGridCell.generated.h"


UCLASS(Blueprintable)
class PREYVSPREDATOR_API UWorldGridCell : public UGridCell
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Grid")
	EWorldCellType Type{EWorldCellType::Grass};

	UPROPERTY(EditAnywhere, Category="Grid")
	float MaxContent{1.f};

	UPROPERTY(EditAnywhere, Category="Grid")
	float ConsumeRate{-0.1f};

	UPROPERTY(EditAnywhere, Category="Grid")
	float RegenRate{0.01f};

public:
	UWorldGridCell() = default;

	void ChangeWorldType(EWorldCellType NewType);
	EWorldCellType WorldType() const;

	bool Occupied() const;
	void Occupy();
	
	float Content() const;
	void Consume();
	void Regenerate();

private:
	bool bOccupied{false};
	float m_Content{MaxContent};

	void SetContents(float Rate);
};