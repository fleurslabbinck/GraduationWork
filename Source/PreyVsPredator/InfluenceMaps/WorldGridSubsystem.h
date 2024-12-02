#pragma once

#include "CoreMinimal.h"
#include "WorldGridCell.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldGridSubsystem.generated.h"


class UGridCell;
class UGrid;

UCLASS()
class PREYVSPREDATOR_API UWorldGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Grid")
	TSubclassOf<UGridCell> GridCellClass{UWorldGridCell::StaticClass()};

	UPROPERTY(EditAnywhere, Category="Grid")
	FVector StartPosition{};

	UPROPERTY(EditAnywhere, Category="Grid")
	uint32 Rows{10};

	UPROPERTY(EditAnywhere, Category="Grid")
	uint32 Columns{10};

	UPROPERTY(EditAnywhere, Category="Grid")
	float CellSize{500.f};

public:
	void SetupGrid();
	UGridCell* NextGrassPatch(const FVector& CurrentPosition) const;

private:
	UPROPERTY()
	UGrid* m_WorldGrid{nullptr};
};
