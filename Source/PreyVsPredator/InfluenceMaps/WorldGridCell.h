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

	UPROPERTY(EditAnywhere, Category="Grid")
	float RegenTime{0.5f};

public:
	UWorldGridCell() = default;

	void ChangeWorldType(EWorldCellType NewType);
	EWorldCellType WorldType() const;
	
	float Content() const;
	bool Consume();
	void Regenerate();

private:
	float m_Content{MaxContent};
	FTimerHandle m_RegenTimer{};

	void SetContents(float Rate);
};