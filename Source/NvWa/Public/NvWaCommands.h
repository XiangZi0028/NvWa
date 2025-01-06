// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "NvWaStyle.h"

class FNvWaCommands : public TCommands<FNvWaCommands>
{
public:

	FNvWaCommands()
		: TCommands<FNvWaCommands>(TEXT("NvWa"), NSLOCTEXT("Contexts", "NvWa", "NvWa Plugin"), NAME_None, FNvWaStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};