#pragma once
#include "CoreMinimal.h"
#include "BHInteractableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UBHInteractableInterface : public UInterface
{
    GENERATED_BODY()
};

class BEHEMOTH_API IBHInteractableInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
    bool CanInteract();
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
    void OnInteract(AActor *InteractInstigator);
};
