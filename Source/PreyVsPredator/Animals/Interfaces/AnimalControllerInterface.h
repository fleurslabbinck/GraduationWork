#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimalControllerInterface.generated.h"


UINTERFACE()
class UAnimalControllerInterface : public UInterface
{
	GENERATED_BODY()
};


class PREYVSPREDATOR_API IAnimalControllerInterface
{
	GENERATED_BODY()

public:

	virtual void SetTimer(const FTimerDelegate& Delegate, float InRate) = 0;
	virtual void ResetTimer() = 0;
};
