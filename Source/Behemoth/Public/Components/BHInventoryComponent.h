#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/BHItemData.h"
#include "BHInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEquippedSignature, const FBHItemData&, ItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUnEquippedSignature, const FBHItemData&, ItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAddedSignature, const FBHItemData&, ItemData, const float, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemovedSignature, const FBHItemData&, ItemData, const float, Amount);

USTRUCT(BlueprintType)
struct FBHInventoryItem
{
	GENERATED_BODY()
	
	FBHInventoryItem()
		: Count(0)
	{
	}

	FBHInventoryItem(const FBHItemData& ItemData, const int32 Amount)
		: Data(ItemData)
		, Count(Amount)
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
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Inventory")
	void ServerAddToInventory(const FBHItemData& ItemData, const int32 Amount = 1);
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Inventory")
	void ServerRemoveFromInventory(const FBHItemData& ItemData, const int32 Amount = 1);

	/* Equipment */
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Equipment")
	void ServerEquipItem(const FBHItemData& ItemData);
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Equipment")
	void ServerUnEquipItem(const FBHItemData& ItemData);


	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemEquippedSignature OnItemEquipped;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemEquippedSignature OnItemUnEquipped;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemAddedSignature OnItemAdded;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemRemovedSignature OnItemRemoved;

protected:
	UFUNCTION(Client, Reliable)
	void ClientAddToInventory(const FBHItemData& ItemData, const int32 Amount = 1);
	void AddToInventory(const FBHItemData& ItemData, const int32 Amount);

	UFUNCTION(Client, Reliable)
	void ClientRemoveFromInventory(const FBHItemData& ItemData, const int32 Amount = 1);
	void RemoveFromInventory(const FBHItemData& ItemData, const int32 Amount);

	UFUNCTION(Client, Reliable)
	void ClientEquipItem(const FBHItemData& ItemData);
	void EquipItem(const FBHItemData& ItemData);

	UFUNCTION(Client, Reliable)
	void ClientUnEquipItem(const FBHItemData& ItemData);
	void UnEquipItem(const FBHItemData& ItemData);
	
protected:
	/* Inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<int32, FBHInventoryItem> Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventorySlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 UsedInventorySlots;

	/* Equipment */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<TEnumAsByte<EBHItemType>, FBHItemData> EquippedItems;

};
