#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactables/BHInteractableInterface.h"

#include "BHInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEHEMOTH_API UBHInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBHInteractionComponent();
	const TScriptInterface<IBHInteractableInterface>& GetCurrentInteractable() const { return CurrentInteractable; }
	
protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	class ABHInteractableBase *FindInteractableObject() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	float InteractDistance;

	TScriptInterface<IBHInteractableInterface> CurrentInteractable;
};
