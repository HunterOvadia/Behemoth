// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "BHItemInfo.generated.h"

UENUM()
enum EBHItemRarity
{
	Common,
	Uncommon,
	Rare,
	Epic
};

UENUM()
enum EBHItemType
{
	// Armor
	Head,
	Shoulders,
	Chest,
	Hands,
	Legs,
	Feet,

	// Weapons
    Sword,
    Axe,
    Staff,
    Bow
};


USTRUCT(BlueprintType)
struct FBHItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EBHItemRarity> Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EBHItemType> Type;
	// TODO(Hunter): Stats
};
