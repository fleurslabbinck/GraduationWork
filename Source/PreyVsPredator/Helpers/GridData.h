﻿#pragma once

#include "CoreMinimal.h"
#include "GridData.generated.h"

//-------------------------------------------------------------------------------------
//	RECT STRUCT
//-------------------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FRect
{
	GENERATED_BODY()
	
	FRect() = default;
	FRect(const FVector& Position, float Size) : Size(Size), Position(Position) {}

	UPROPERTY(EditAnywhere)
	float Size{};

	UPROPERTY(EditAnywhere)
	FVector Position{FVector::ZeroVector};
};


//-------------------------------------------------------------------------------------
//	WORLD TYPE ENUM
//-------------------------------------------------------------------------------------

UENUM(BlueprintType)
enum class EWorldCellType : uint8
{
	Grass UMETA(DisplayName="GRASS"),
	Water UMETA(DisplayName="WATER"),
	Carcass UMETA(DisplayName="CARCASS"),
	None UMETA(DisplayName="NONE")
};
