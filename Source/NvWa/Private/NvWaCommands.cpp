// Copyright Epic Games, Inc. All Rights Reserved.

#include "NvWaCommands.h"

#define LOCTEXT_NAMESPACE "FNvWaModule"

void FNvWaCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "NvWa", "Bring up NvWa window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
