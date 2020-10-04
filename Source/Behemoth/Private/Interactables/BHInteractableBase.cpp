// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/BHInteractableBase.h"

ABHInteractableBase::ABHInteractableBase()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComponent->SetupAttachment(RootComponent);
}
