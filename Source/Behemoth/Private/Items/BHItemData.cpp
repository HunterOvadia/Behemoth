// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BHItemData.h"

FAttributeData::FAttributeData()
    : Type()
    , Amount(0)
{
}

FBHItemData::FBHItemData()
    : ID(-1)
    , ItemIcon(nullptr)
    , ItemMesh(nullptr)
    , Rarity()
    , Type()
{
}
