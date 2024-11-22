#pragma once

#include "CoreMinimal.h"
#include "GridCells.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldGridSubsystem.generated.h"


UCLASS()
class PREYVSPREDATOR_API UWorldGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 Rows{10};

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 Columns{10};

	UPROPERTY(EditAnywhere, Category="Grid")
	float CellSize{100.f};

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	TArray<TArray<FWorldCell>> WorldGrid;
	
};
