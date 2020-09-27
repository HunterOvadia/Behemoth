// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define BH_LOG(text) UE_LOG(LogTemp, Warning, TEXT(text));
#define BG_LOG_SCREEN(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1f, FColor::Red, TEXT(text));