// Copyright Epic Games, Inc. All Rights Reserved.

#include "Behemoth.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Behemoth, "Behemoth" );

void BH_DebugPrintStringToScreen(UWorld* World, const FString& InString)
{
    if(GEngine != nullptr)
    {
        FString Prefix = "";
        ENetMode NetMode = NM_Client;
        if(World != nullptr)
        {
            if(World->WorldType == EWorldType::PIE)
            {
                switch(NetMode = World->GetNetMode())
                {
                case NM_DedicatedServer:
                case NM_ListenServer:
                {
                    Prefix = FString::Printf(TEXT("[SERVER]: "));
                    break;
                }
                case NM_Client:
                {
                    Prefix = FString::Printf(TEXT("[CLIENT %d]: "), GPlayInEditorID - 1);
                    break;
                }             
                default:
                {
                    break;
                }
                }
            }
        }

        const FString FinalString = (Prefix + InString);
        if(GAreScreenMessagesEnabled)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, NetMode == NM_Client ? FColor::Red : FColor::Green, FinalString);
        }
    }
}
