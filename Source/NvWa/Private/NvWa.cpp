// Copyright Epic Games, Inc. All Rights Reserved.

#include "NvWa.h"
#include "NvWaStyle.h"
#include "NvWaCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName NvWaTabName("NvWa");

#define LOCTEXT_NAMESPACE "FNvWaModule"

void FNvWaModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FNvWaStyle::Initialize();
	FNvWaStyle::ReloadTextures();

	FNvWaCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNvWaCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FNvWaModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNvWaModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(NvWaTabName, FOnSpawnTab::CreateRaw(this, &FNvWaModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FNvWaTabTitle", "NvWa"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FNvWaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FNvWaStyle::Shutdown();

	FNvWaCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NvWaTabName);
}

TSharedRef<SDockTab> FNvWaModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FNvWaModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("NvWa.cpp"))
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

void FNvWaModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(NvWaTabName);
}

void FNvWaModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FNvWaCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FNvWaCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNvWaModule, NvWa)