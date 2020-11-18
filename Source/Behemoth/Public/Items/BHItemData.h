// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BHAttributesComponent.h"
#include "Engine/DataTable.h"

#include "BHItemData.generated.h"

UENUM(BlueprintType)
enum EBHItemRarity
{
	Common,
	Uncommon,
	Rare,
	Epic
};


UENUM(BlueprintType)
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
	PrimaryWeapon,
	SecondaryWeapon,
};

USTRUCT(BlueprintType)
struct FAttributeData
{
	GENERATED_BODY()
	FAttributeData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EBHAttributeType> Type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Amount;
};

USTRUCT(BlueprintType)
struct FBHItemData : public FTableRowBase
{
	GENERATED_BODY()
	FBHItemData();

public:
	friend bool operator==(const FBHItemData& Lhs, const FBHItemData& Rhs) { return Lhs.ID == Rhs.ID; }
	explicit operator bool() const { return ID > 0; }

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D *ItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh *ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EBHItemRarity> Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EBHItemType> Type;

	// UPDATE(Hunter): Had to change this to an array because TMap's can't be replicated
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAttributeData> Attributes;
};
