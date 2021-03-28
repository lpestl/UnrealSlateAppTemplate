// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSlateAppTemplateModule/Public/UnrealSlateAppTemplateModuleCommands.h"

#define LOCTEXT_NAMESPACE "FUnrealSlateAppTemplateModuleModule"

void FUnrealSlateAppTemplateModuleCommands::RegisterCommands()
{
	UI_COMMAND(OpenMainWindow, "UnrealSlateAppTemplateModule", "Bring up UnrealSlateAppTemplateModule window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
