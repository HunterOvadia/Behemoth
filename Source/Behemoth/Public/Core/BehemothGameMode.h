#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "Items/BHItemInfo.h"

#include "BehemothGameMode.generated.h"

UCLASS(minimalapi)
class ABehemothGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABehemothGameMode();

	UFUNCTION(BlueprintCallable, Category = "Items")
	UDataTable *GetItemDatabase() const { return ItemDatabase; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Database")
	UDataTable *ItemDatabase;
};



