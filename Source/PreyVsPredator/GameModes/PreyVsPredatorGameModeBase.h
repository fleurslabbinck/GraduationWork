#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PreyVsPredatorGameModeBase.generated.h"


class UGrid;

UCLASS()
class PREYVSPREDATOR_API APreyVsPredatorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
