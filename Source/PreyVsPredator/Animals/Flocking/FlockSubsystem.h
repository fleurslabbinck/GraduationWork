#pragma once

#include "CoreMinimal.h"
#include "BaseFlock.h"
#include "Subsystems/WorldSubsystem.h"
#include "FlockSubsystem.generated.h"


class ABaseFlock;

UCLASS()
class PREYVSPREDATOR_API UFlockSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	ABaseFlock* CreateFlock();
	void MergeFlocks(ABaseFlock* Flock1, ABaseFlock* Flock2);

private:
	UPROPERTY()
	TArray<ABaseFlock*> m_Flocks;

	UFUNCTION()
	void UpdateFlocks();
};
