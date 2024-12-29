#pragma once

#include "CoreMinimal.h"
#include "PreyVsPredator/Helpers/GridData.h"
#include "UObject/Object.h"
#include "GridCell.generated.h"

UCLASS(Blueprintable)
class PREYVSPREDATOR_API UGridCell : public UObject
{
	GENERATED_BODY()

public:
	UGridCell() = default;
	
	virtual void Initialize(const FVector GridPosition, float CellSize);
	void DrawDebugCell(uint32 Index) const;
	
	FRect GridCell() const;
	FVector CenterPosition() const;

	virtual bool Available() const;
	void SetAvailability(bool Available);

private:
	bool bAvailable{true};
	FRect m_Cell;
};
