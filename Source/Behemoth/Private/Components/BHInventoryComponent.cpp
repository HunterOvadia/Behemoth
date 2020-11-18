// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BHInventoryComponent.h"

UBHInventoryComponent::UBHInventoryComponent()
    : MaxInventorySlots(32)
    , UsedInventorySlots(0)
{
}

void UBHInventoryComponent::AddToInventory(const FBHItemData& ItemData, const int32 Amount)
{
    // NOTE(Hunter): If we have an item in our inventory, just add to the value.
    if(Inventory.Find(ItemData.ID))
    {
        int32& ItemCount = Inventory[ItemData.ID].Count;
        ++ItemCount;
    }
    else // NOTE(Hunter): If we do not have the item in our inventory, make a new one with the amount
    {
        if(UsedInventorySlots < MaxInventorySlots)
        {
            Inventory.Add(ItemData.ID, FBHInventoryItem(ItemData, Amount));
            ++UsedInventorySlots;
        }
    }

    OnItemAdded.Broadcast(ItemData, Amount);
}
void UBHInventoryComponent::ServerAddToInventory_Implementation(const FBHItemData& ItemData, const int32 Amount)
{
    AddToInventory(ItemData, Amount);
    ClientAddToInventory(ItemData, Amount);
}
bool UBHInventoryComponent::ServerAddToInventory_Validate(const FBHItemData& ItemData, const int32 Amount)
{
    return true;
}
void UBHInventoryComponent::ClientAddToInventory_Implementation(const FBHItemData& ItemData, const int32 Amount)
{
    AddToInventory(ItemData, Amount);
}

void UBHInventoryComponent::RemoveFromInventory(const FBHItemData& ItemData, const int32 Amount)
{
    // NOTE(Hunter): If we have an item in our inventory, reduce the amount
    if(Inventory.Find(ItemData.ID))
    {
        int32& ItemCount = Inventory[ItemData.ID].Count;

        // NOTE(Hunter): If we have more than one item, remove the amount
        if(ItemCount > 1)
        {
            ItemCount -= Amount;

            // NOTE(Hunter): If we have 0 or less than 0, remove it.
            if(ItemCount <= 0)
            {
                Inventory.Remove(ItemData.ID);
                --UsedInventorySlots;
            }
        }
        else // NOTE(Hunter): If we only have 1 item, just remove it.
        {
            Inventory.Remove(ItemData.ID);
            --UsedInventorySlots;
        }

        OnItemRemoved.Broadcast(ItemData, Amount);
    }
}
void UBHInventoryComponent::ServerRemoveFromInventory_Implementation(const FBHItemData& ItemData, const int32 Amount)
{
    RemoveFromInventory(ItemData, Amount);
    ClientRemoveFromInventory(ItemData, Amount);
}
bool UBHInventoryComponent::ServerRemoveFromInventory_Validate(const FBHItemData& ItemData, const int32 Amount)
{
    return true;
}
void UBHInventoryComponent::ClientRemoveFromInventory_Implementation(const FBHItemData& ItemData, const int32 Amount)
{
    RemoveFromInventory(ItemData, Amount);
}

void UBHInventoryComponent::EquipItem(const FBHItemData& ItemData)
{
    const bool HasItemEquippedInSlot = EquippedItems.Contains(ItemData.Type);
    if(HasItemEquippedInSlot)
    {
        const FBHItemData CurrentlyEquippedItemInSlot = EquippedItems[ItemData.Type];
        if(CurrentlyEquippedItemInSlot)
        {
            ServerUnEquipItem(CurrentlyEquippedItemInSlot);
        }
    }

    EquippedItems.Add(ItemData.Type, ItemData);
    ServerRemoveFromInventory(ItemData, 1);

    OnItemEquipped.Broadcast(ItemData);
}
void UBHInventoryComponent::ServerEquipItem_Implementation(const FBHItemData& ItemData)
{
    EquipItem(ItemData);
    ClientEquipItem(ItemData);
}
bool UBHInventoryComponent::ServerEquipItem_Validate(const FBHItemData& ItemData)
{
    return true;
}
void UBHInventoryComponent::ClientEquipItem_Implementation(const FBHItemData& ItemData)
{
    EquipItem(ItemData);
}

void UBHInventoryComponent::UnEquipItem(const FBHItemData& ItemData)
{
    EquippedItems.Remove(ItemData.Type);
    ServerAddToInventory(ItemData, 1);

    OnItemUnEquipped.Broadcast(ItemData);
}
void UBHInventoryComponent::ServerUnEquipItem_Implementation(const FBHItemData& ItemData)
{
    UnEquipItem(ItemData);
    ClientUnEquipItem(ItemData);
}
bool UBHInventoryComponent::ServerUnEquipItem_Validate(const FBHItemData& ItemData)
{
    return true;
}
void UBHInventoryComponent::ClientUnEquipItem_Implementation(const FBHItemData& ItemData)
{
    UnEquipItem(ItemData);
}



