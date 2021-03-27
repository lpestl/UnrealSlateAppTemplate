// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ISlateReflectorModule.h"
#include "UnrealSlateAppTemplate.h"
#include "Widgets/Docking/SDockTab.h"


/**
 * Run the UnrealSlateAppTemplate .
 */
int RunUnrealSlateAppTemplate(const TCHAR* Commandline);

/**
 * Spawn the contents of the web browser tab
 */
TSharedRef<SDockTab> SpawnWebBrowserTab(const FSpawnTabArgs& Args);
