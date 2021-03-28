// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSlateAppTemplateApp.h"
#include "UnrealSlateAppTemplateModule/Public/UnrealSlateAppTemplateModule.h"

#include "Runtime/Launch/Public/RequiredProgramMainCPPInclude.h"
#include "Framework/Application/SlateApplication.h"

IMPLEMENT_APPLICATION(UnrealSlateAppTemplate, "UnrealSlateAppTemplate");

#define LOCTEXT_NAMESPACE "UnrealSlateAppTemplate"

namespace WorkspaceMenu
{
	TSharedRef<FWorkspaceItem> DeveloperMenu = FWorkspaceItem::NewGroup(LOCTEXT("DeveloperMenu", "Developer"));
}


int RunUnrealSlateAppTemplate( const TCHAR* CommandLine )
{
	// start up the main loop
	GEngineLoop.PreInit(CommandLine);

	// Make sure all UObject classes are registered and default properties have been initialized
	ProcessNewlyLoadedUObjects();
	
	// Tell the module manager it may now process newly-loaded UObjects when new C++ modules are loaded
	FModuleManager::Get().StartProcessingNewlyLoadedObjects();

	// crank up a normal Slate application using the platform's standalone renderer
	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());

	// set the application name
	FGlobalTabmanager::Get()->SetApplicationTitle(LOCTEXT("AppTitle", "Slate Viewer"));

	// launch the main window of the UnrealSlateAppTemplate module
	FUnrealSlateAppTemplateModule& UnrealSlateAppTemplateModule = FModuleManager::LoadModuleChecked<FUnrealSlateAppTemplateModule>(FName("UnrealSlateAppTemplateModule"));
	UnrealSlateAppTemplateModule.PluginButtonClicked();
	
	// loop while the server does the rest
	while (!IsEngineExitRequested())
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		FStats::AdvanceFrame(false);
		FTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();		
		FPlatformProcess::Sleep(0);
	}

	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();


	return 0;
}

#undef LOCTEXT_NAMESPACE
