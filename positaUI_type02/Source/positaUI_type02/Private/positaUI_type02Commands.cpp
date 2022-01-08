// Copyright Epic Games, Inc. All Rights Reserved.

#include "positaUI_type02Commands.h"

#define LOCTEXT_NAMESPACE "FpositaUI_type02Module"

void FpositaUI_type02Commands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "positaUI_type02", "Bring up positaUI_type02 window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
