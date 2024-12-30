#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "UObject/Object.h"
#include "WorldGridCell.generated.h"


class AStaticMeshActor;

UCLASS(Blueprintable)
class PREYVSPREDATOR_API UWorldGridCell : public UGridCell
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Grid")
	EWorldCellType Type{EWorldCellType::Grass};

	UPROPERTY(EditAnywhere, Category="Grid|Mesh")
	UStaticMesh* GridCellMesh;

	UPROPERTY(EditAnywhere, Category="Grid|Mesh")
	float MeshScale{100.f};

	UPROPERTY(EditAnywhere, Category="Grid|Color")
	FLinearColor GrassColor{0, 1.f, 0.f, 1.f};

	UPROPERTY(EditAnywhere, Category="Grid|Color")
	FLinearColor DirtColor{1.f, 0.5f, 0.f, 1.f};

	UPROPERTY(EditAnywhere, Category="Grid|Color")
	FLinearColor WaterColor{0, 0.5f, 1.f, 1.f};

	UPROPERTY(EditAnywhere, Category="Grid|Color")
	FName CellColorParameter{"Color"};
	
	UPROPERTY(EditAnywhere, Category="Grid|Content")
	float MaxContent{1.f};

	UPROPERTY(EditAnywhere, Category="Grid|Content")
	float ConsumeRate{-0.05f};

	UPROPERTY(EditAnywhere, Category="Grid|Content")
	float RegenRate{0.001f};

	UPROPERTY(EditAnywhere, Category="Grid|Content")
	float RegenTime{0.5f};

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 MaxEntities{2};

public:
	UWorldGridCell() = default;

	virtual void Initialize(const FVector GridPosition, float CellSize) override;

	void ChangeWorldType(EWorldCellType NewType);
	EWorldCellType WorldType() const;

	virtual bool Available() const override;
	void Subscribe(AActor* EntityToAdd);
	void Unsubscribe(AActor* EntityToRemove);
	
	float Content() const;
	bool Consume();
	void Regenerate();

private:
	bool bRegenerating{false};
	float m_Content{MaxContent};
	FTimerHandle m_RegenTimer{};

	UPROPERTY()
	AStaticMeshActor* m_StaticMesh{nullptr};

	UPROPERTY()
	UMaterialInstanceDynamic* m_CellMaterial{nullptr};

	UPROPERTY()
	TArray<AActor*> m_SubscribedEntities;

	void SetCellColor(FLinearColor NewColor) const;
	void SetContents(float Rate);
};