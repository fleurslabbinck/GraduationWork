#pragma once

#include "CoreMinimal.h"
#include "GridData.h"
#include "UObject/Object.h"
#include "GridCell.generated.h"

UCLASS(Blueprintable)
class PREYVSPREDATOR_API UGridCell : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Grid")
	FRect Cell;

public:
	UGridCell() = default;
	
	virtual void Initialize(const FVector2D GridPosition, float CellSize);
	void DrawDebugCell(uint32 Index) const;
	
	FRect GridCell() const;
	FVector2D CenterPosition() const;
};
