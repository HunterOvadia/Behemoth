// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BHAttributesComponent.h"
#include "Engine/DataTable.h"

#include "BHItemInfo.generated.h"

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
};


USTRUCT(BlueprintType)
struct FBHItemData : public FTableRowBase
{
	GENERATED_BODY()
	FBHItemData();

public:
	friend bool operator==(const FBHItemData& Lhs, const FBHItemData& Rhs)
	{
		return Lhs.ID == Rhs.ID;
	}
	
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<EBHAttributeType>, int32> Attributes;

	
};
