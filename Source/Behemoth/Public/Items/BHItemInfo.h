// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
enum EBHArmorType
{
	Head,
	Shoulders,
	Chest,
	Hands,
	Legs,
	Feet,
};

UENUM()
enum EBHWeaponType
{
    Sword,
	Axe,
	Staff,
	Bow
};


USTRUCT(BlueprintType)
struct FBHItemData
{
	GENERATED_BODY()

	int ID;
	FText Name;
	TEnumAsByte<EBHItemRarity> Rarity;
	// Generic Stats
};

USTRUCT(BlueprintType)
struct FBHArmorData : public FBHItemData
{
	GENERATED_BODY()
	TEnumAsByte<EBHArmorType> Type;
};

USTRUCT(BlueprintType)
struct FBHWeaponData : public FBHItemData
{
	GENERATED_BODY()
	TEnumAsByte<EBHWeaponType> Type;

	float Damage;
	float Speed;
};