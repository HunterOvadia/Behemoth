// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BHGameInstance.h"

UBHGameInstance::UBHGameInstance()
{
}

FBHItemData* UBHGameInstance::GetItemByID(const uint32 ID) const
{
    check(ItemDatabase);
    return ItemDatabase->FindRow<FBHItemData>(FName(FString::FromInt(ID)), "");
}
