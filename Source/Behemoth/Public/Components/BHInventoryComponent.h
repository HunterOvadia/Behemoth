#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/BHItemInfo.h"
#include "BHInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEquippedSignature, const FBHItemData&, ItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUnEquippedSignature, const FBHItemData&, ItemData);

USTRUCT(BlueprintType)
struct FBHInventoryItem
{
	GENERATED_BODY()
	
	FBHInventoryItem()
		: Count(0)
	{
	}

	FBHInventoryItem(const FBHItemData& ItemData, const int32 Amount)
		: Data(ItemData), Count(Amount)
	{
	}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBHItemData Data;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Count;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEHEMOTH_API UBHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBHInventoryComponent();

	/* Inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddToInventory(const FBHItemData& ItemData, const int32 Amount = 1);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveFromInventory(const FBHItemData& ItemData, const int32 Amount = 1);

	/* Equipment */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipItem(const FBHItemData& ItemData);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UnEquipItem(const FBHItemData& ItemData);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemEquippedSignature OnItemEquipped;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemEquippedSignature OnItemUnEquipped;
	
protected:
	/* Inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<int32, FBHInventoryItem> Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaxInventorySlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 UsedInventorySlots;

	/* Equipment */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<TEnumAsByte<EBHItemType>, FBHItemData> EquippedItems;

};
