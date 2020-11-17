// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/BHItemPickup.h"
#include "Character/BehemothCharacter.h"
#include "Components/BHInventoryComponent.h"
#include "Core/BHGameInstance.h"

void ABHItemPickup::BeginPlay()
{
    Super::BeginPlay();

    if(ItemID > 0)
    {
        UBHGameInstance *GameInstance = Cast<UBHGameInstance>(GetGameInstance());
        if(IsValid(GameInstance))
        {
            FBHItemData* Item = GameInstance->GetItemByID(ItemID);
            if(Item != nullptr)
            {
                OwningItemData = *Item;
            }
        }
    }
    
    if(IsValid(StaticMeshComponent) && OwningItemData)
    {
        StaticMeshComponent->SetStaticMesh(OwningItemData.ItemMesh);
    }
}

bool ABHItemPickup::CanInteract_Implementation()
{
    return true;
}

void ABHItemPickup::OnInteract_Implementation(AActor *InteractInstigator)
{
    if(OwningItemData)
    {
        ABehemothCharacter *Character = Cast<ABehemothCharacter>(InteractInstigator);
        if(IsValid(Character))
        {
            Character->GetInventoryComponent()->AddToInventory(OwningItemData);
            Destroy();
        }
    }
}
