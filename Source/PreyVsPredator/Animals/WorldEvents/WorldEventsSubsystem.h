#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldEventsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEntityDeath);

UCLASS()
class PREYVSPREDATOR_API UWorldEventsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	FOnEntityDeath OnEntityDeath;
};
