#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/BHItemInfo.h"
#include "BHInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEHEMOTH_API UBHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBHInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddToInventory(const FBHItemData& ItemData);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FBHItemData> Inventory;
};
