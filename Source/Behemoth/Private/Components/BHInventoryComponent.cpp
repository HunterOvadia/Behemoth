// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BHInventoryComponent.h"

#include "Behemoth/Behemoth.h"

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
    else
    {
        if(UsedInventorySlots < MaxInventorySlots)
        {
            // NOTE(Hunter): If we do not have the item in our inventory, make a new one with the amount
            Inventory.Add(ItemData.ID, FBHInventoryItem(ItemData, Amount));
            ++UsedInventorySlots;
        }
    }
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
        else
        {
            // NOTE(Hunter): If we only have 1 item, just remove it.
            Inventory.Remove(ItemData.ID);
            --UsedInventorySlots;
        }
    }
}

void UBHInventoryComponent::EquipItem(const FBHItemData& ItemData)
{
    // TODO(Hunter): Currently a bug with stats not recalculating properly when equipping an item in a slot that already has an item.
    const bool HasItemEquippedInSlot = EquippedItems.Contains(ItemData.Type) && EquippedItems[ItemData.Type].ID > 0;
    if(HasItemEquippedInSlot)
    {
        const FBHItemData& CurrentlyEquippedItemInSlot = EquippedItems[ItemData.Type];
        if(CurrentlyEquippedItemInSlot)
        {
            UnEquipItem(CurrentlyEquippedItemInSlot);
        }
    }

    EquippedItems.Add(ItemData.Type, ItemData);
    RemoveFromInventory(ItemData, 1);

    
    OnItemEquipped.Broadcast(ItemData);
}

void UBHInventoryComponent::UnEquipItem(const FBHItemData& ItemData)
{
    EquippedItems.Remove(ItemData.Type);
    AddToInventory(ItemData, 1);

    OnItemUnEquipped.Broadcast(ItemData);
}

