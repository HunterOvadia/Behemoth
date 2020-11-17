
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Items/BHItemData.h"

#include "BHGameInstance.generated.h"

UCLASS()
class BEHEMOTH_API UBHGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UBHGameInstance();
	
	UFUNCTION(BlueprintCallable, Category = "Items")
    UDataTable *GetItemDatabase() const { return ItemDatabase; }
	FBHItemData *GetItemByID(uint32 ID) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Database")
	UDataTable *ItemDatabase;
};
