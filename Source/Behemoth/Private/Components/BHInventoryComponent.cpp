// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BHInventoryComponent.h"

UBHInventoryComponent::UBHInventoryComponent()
{

}

void UBHInventoryComponent::AddToInventory(const FBHItemData& ItemData)
{
    Inventory.Add(ItemData);
}



