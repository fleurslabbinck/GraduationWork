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

	UPROPERTY(EditAnywhere, Category="Grid")
	UStaticMesh* GridCellMesh;

	UPROPERTY(EditAnywhere, Category="Grid")
	FLinearColor GrassColor{0, 1.f, 0.f, 1.f};

	UPROPERTY(EditAnywhere, Category="Grid")
	FLinearColor DirtColor{1.f, 0.5f, 0.f, 1.f};

	UPROPERTY(EditAnywhere, Category="Grid")
	FLinearColor WaterColor{0, 0.5f, 1.f, 1.f};
	
	UPROPERTY(EditAnywhere, Category="Grid")
	float MeshScale{100.f};
	
	UPROPERTY(EditAnywhere, Category="Grid")
	float MaxContent{1.f};

	UPROPERTY(EditAnywhere, Category="Grid")
	float ConsumeRate{-0.05f};

	UPROPERTY(EditAnywhere, Category="Grid")
	float RegenRate{0.001f};

	UPROPERTY(EditAnywhere, Category="Grid")
	float RegenTime{0.5f};

	UPROPERTY(EditAnywhere, Category="Grid")
	FName CellColorParameter{"Color"};

public:
	UWorldGridCell() = default;

	virtual void Initialize(const FVector GridPosition, float CellSize) override;

	void ChangeWorldType(EWorldCellType NewType);
	EWorldCellType WorldType() const;
	
	float Content() const;
	bool Consume();
	void Regenerate();

private:
	float m_Content{MaxContent};
	FTimerHandle m_RegenTimer{};

	UPROPERTY()
	AStaticMeshActor* m_StaticMesh{nullptr};

	UPROPERTY()
	UMaterialInstanceDynamic* m_CellMaterial{nullptr};

	void SetCellColor(FLinearColor NewColor) const;
	void SetContents(float Rate);
};