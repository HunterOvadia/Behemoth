#include "Components/BHInteractionComponent.h"
#include "Interactables/BHInteractableBase.h"
#include "DrawDebugHelpers.h"
#include "Interactables/BHInteractableInterface.h"


UBHInteractionComponent::UBHInteractionComponent()
	: InteractDistance(200.0f)
{
	PrimaryComponentTick.bCanEverTick = true;
}

ABHInteractableBase* UBHInteractionComponent::FindInteractableObject() const
{
	UWorld *World = GetWorld();
	if(World != nullptr)
	{
		FVector OutLocation;
		FRotator OutRotation;
		GetOwner()->GetActorEyesViewPoint(OutLocation, OutRotation);

		FVector Start = OutLocation;
		FVector End = (Start + (OutRotation.Vector() * InteractDistance));

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
	
		FHitResult HitResult;
		if(World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
		{
			if(ABHInteractableBase *InteractableResult = Cast<ABHInteractableBase>(HitResult.GetActor()))
			{
				return InteractableResult;
			}
		}
	}

	return nullptr;
}

void UBHInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ABHInteractableBase *CurrentHit = FindInteractableObject())
	{
		if(UStaticMeshComponent *HitMesh = CurrentHit->GetMesh())
		{
			HitMesh->SetRenderCustomDepth(true);
		}
		
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
			if(ABHInteractableBase *InteractableBase = Cast<ABHInteractableBase>(CurrentInteractable.GetObject()))
			{
				if(UStaticMeshComponent *InteractableMesh = InteractableBase->GetMesh())
				{
					InteractableMesh->SetRenderCustomDepth(false);
				}
			}
			
			CurrentInteractable = nullptr;
		}
	}
}

