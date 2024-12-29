#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseFlock.generated.h"


class ABaseEntity;

UCLASS()
class PREYVSPREDATOR_API ABaseFlock : public AActor
{
	GENERATED_BODY()

public:
	uint32 TotalEntities() const;
	TArray<ABaseEntity*> Entities();
	
	void AddEntity(ABaseEntity* NewEntity);
	void RemoveEntity(ABaseEntity* EntityToRemove);

	bool Thirsty() const;
	void SetThirsty(bool Thirsty);
	FVector FlockLocation() const;

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
private:
	bool bThirsty{false};
	
	UPROPERTY()
	TArray<ABaseEntity*> m_Entities;
};
