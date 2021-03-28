// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSlateAppTemplateModule/Public/UnrealSlateAppTemplateModule.h"
#include "UnrealSlateAppTemplateModule/Public/UnrealSlateAppTemplateModuleStyle.h"
#include "UnrealSlateAppTemplateModule/Public/UnrealSlateAppTemplateModuleCommands.h"

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

static const FName UnrealSlateAppTemplateModuleTabName("UnrealSlateAppTemplateModule");

#define LOCTEXT_NAMESPACE "FUnrealSlateAppTemplateModule"

void FUnrealSlateAppTemplateModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; 
	
	FUnrealSlateAppTemplateModuleStyle::Initialize();
	FUnrealSlateAppTemplateModuleStyle::ReloadTextures();

	FUnrealSlateAppTemplateModuleCommands::Register();
	
	AppCommands = MakeShareable(new FUICommandList);

	AppCommands->MapAction(
		FUnrealSlateAppTemplateModuleCommands::Get().OpenMainWindow,
		FExecuteAction::CreateRaw(this, &FUnrealSlateAppTemplateModule::AppStarted),
		FCanExecuteAction());
		
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(UnrealSlateAppTemplateModuleTabName, FOnSpawnTab::CreateRaw(this, &FUnrealSlateAppTemplateModule::OnSpawnMainTab))
		.SetDisplayName(LOCTEXT("FUnrealSlateAppTemplateModuleTabTitle", "UnrealSlateAppTemplateModule"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FUnrealSlateAppTemplateModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	FUnrealSlateAppTemplateModuleStyle::Shutdown();

	FUnrealSlateAppTemplateModuleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(UnrealSlateAppTemplateModuleTabName);
}

TSharedRef<SDockTab> FUnrealSlateAppTemplateModule::OnSpawnMainTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FUnrealSlateAppTemplateModule::OnSpawnMainTab")),
		FText::FromString(TEXT("UnrealSlateAppTemplateModule.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FUnrealSlateAppTemplateModule::AppStarted()
{
	FGlobalTabmanager::Get()->TryInvokeTab(UnrealSlateAppTemplateModuleTabName);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnrealSlateAppTemplateModule, UnrealSlateAppTemplateModule)