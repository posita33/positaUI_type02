// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "positaUI_type02Style.h"

class FpositaUI_type02Commands : public TCommands<FpositaUI_type02Commands>
{
public:

	FpositaUI_type02Commands()
		: TCommands<FpositaUI_type02Commands>(TEXT("positaUI_type02"), NSLOCTEXT("Contexts", "positaUI_type02", "positaUI_type02 Plugin"), NAME_None, FpositaUI_type02Style::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};