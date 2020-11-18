// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/BHInteractableBase.h"
#include "Items/BHItemData.h"

#include "BHItemPickup.generated.h"

/**
 * 
 */
UCLASS()
class BEHEMOTH_API ABHItemPickup : public ABHInteractableBase
{
	GENERATED_BODY()
    virtual void BeginPlay() override;

    virtual bool CanInteract_Implementation() override;
    virtual void OnInteract_Implementation(AActor* InteractInstigator) override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    int32 ItemID;
    
    UPROPERTY(BlueprintReadOnly, Category = "Item")
    FBHItemData OwningItemData;
};
