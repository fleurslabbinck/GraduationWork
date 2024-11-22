#pragma once

#include "CoreMinimal.h"
#include "GridCells.generated.h"


UENUM(BlueprintType)
enum class EWorldCellType : uint8
{
	Grass UMETA(DisplayName="GRASS"),
	Water UMETA(DisplayName="Water")
};

USTRUCT(BlueprintType)
struct FWorldCell
{
	GENERATED_BODY()

private:
	bool bTaken{false};
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Grid")
	EWorldCellType Type{EWorldCellType::Grass};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Grid")
	float MaxContent{1.f};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Grid")
	float Content{MaxContent};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Grid")
	FVector2D GridPosition{};
	
public:
	explicit FWorldCell(const FVector2D GridPosition) : GridPosition(GridPosition) {}
	~FWorldCell() = default;

	bool IsTaken() const {return bTaken;}
	void SetTaken() {bTaken = true;}
	
	float GetContentState() const {return Content;}
	void ConsumeContent(float ConsumeRate)
	{
		Content = FMath::Clamp(Content - ConsumeRate, 0, Content);
	}
	void RegenerateContent(float RegenerationRate)
	{
		Content = FMath::Clamp(Content + RegenerationRate, 0, MaxContent);
	}
};