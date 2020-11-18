// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

void BH_DebugPrintStringToScreen(UWorld *World, const FString& InString);

#define BH_LOG(text) UE_LOG(LogTemp, Warning, TEXT(text));
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
#define BH_LOG_SCREEN(World, String) { BH_DebugPrintStringToScreen(World, String); }
#else
#define BH_LOG_SCREEN(x)
#endif
