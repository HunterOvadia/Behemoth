
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "BHGameInstance.generated.h"

UCLASS()
class BEHEMOTH_API UBHGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UBHGameInstance();
	
	UFUNCTION(BlueprintCallable, Category = "Items")
    UDataTable *GetItemDatabase() const { return ItemDatabase; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Database")
	UDataTable *ItemDatabase;
};
