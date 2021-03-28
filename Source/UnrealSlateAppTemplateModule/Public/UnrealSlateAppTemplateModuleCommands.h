// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "UnrealSlateAppTemplateModuleStyle.h"

class FUnrealSlateAppTemplateModuleCommands : public TCommands<FUnrealSlateAppTemplateModuleCommands>
{
public:

	FUnrealSlateAppTemplateModuleCommands()
		: TCommands<FUnrealSlateAppTemplateModuleCommands>(TEXT("UnrealSlateAppTemplateModule"), NSLOCTEXT("Contexts", "UnrealSlateAppTemplateModule", "UnrealSlateAppTemplateModule application"), NAME_None, FUnrealSlateAppTemplateModuleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenMainWindow;
};