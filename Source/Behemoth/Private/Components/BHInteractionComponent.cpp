#include "Components/BHInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "Interactables/BHInteractableInterface.h"


UBHInteractionComponent::UBHInteractionComponent()
{
	InteractDistance = 200.0f;
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UBHInteractionComponent::FindInteractableObject() const
{
	UWorld *World = GetWorld();
	if(World != nullptr)
	{
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = (Start + (GetOwner()->GetActorForwardVector() * InteractDistance));

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
	
		FHitResult HitResult;
		if(World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
		{
			return HitResult.GetActor();
		}
	}

	return nullptr;
}

void UBHInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(AActor *CurrentHit = FindInteractableObject())
	{
		IBHInteractableInterface *Interactable = Cast<IBHInteractableInterface>(CurrentHit);
		if(Interactable != nullptr && CurrentHit != CurrentInteractable.GetObject())
		{
			CurrentInteractable.SetObject(CurrentHit);
			CurrentInteractable.SetInterface(Interactable);
		}
	}
	else
	{
		if(CurrentInteractable != nullptr)
		{
			CurrentInteractable = nullptr;
		}
	}
}
