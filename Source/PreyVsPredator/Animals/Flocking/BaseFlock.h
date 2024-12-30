#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseFlock.generated.h"


class ABaseEntity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFlockEmpty);

UCLASS()
class PREYVSPREDATOR_API ABaseFlock : public AActor
{
	GENERATED_BODY()

public:
	uint32 TotalEntities() const;
	TArray<ABaseEntity*> Entities();
	
	void AddEntity(ABaseEntity* NewEntity);
	void RemoveEntity(ABaseEntity* EntityToRemove);

	bool Hungry() const;
	bool Thirsty() const;
	void SetHungry();
	void SetThirsty();
	void ResetNeeds();
	FVector FlockLocation() const;

	FOnFlockEmpty OnFlockEmpty;

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
private:
	bool bHungry{false};
	bool bThirsty{false};
	
	UPROPERTY()
	TArray<ABaseEntity*> m_Entities;
};
