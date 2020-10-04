// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BHInteractableInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BHInteractableBase.generated.h"

UCLASS()
class BEHEMOTH_API ABHInteractableBase : public AActor, public IBHInteractableInterface
{
	GENERATED_BODY()
	
public:	
	ABHInteractableBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	FName DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	UStaticMeshComponent *StaticMeshComponent;

};
