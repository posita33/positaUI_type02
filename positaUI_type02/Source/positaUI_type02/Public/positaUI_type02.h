// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FpositaUI_type02Module : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	// Add Function
	// X���W���̊֐�
	TOptional<int32> GetCoordinate2DX() const { return Coordinate2D.X; }
	void SetCoordinate2DX(int32 NewValue);
	void SetCoordinate2DXCommit(int32 NewValue, ETextCommit::Type);

	// Y���W���̊֐�
	TOptional<int32> GetCoordinate2DY() const { return Coordinate2D.Y; }
	void SetCoordinate2DY(int32 NewValue);
	void SetCoordinate2DYCommit(int32 NewValue, ETextCommit::Type);

	// CoordinateButton���N���b�N�������̏���
	FReply CoordinateButtonClicked();

private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	// Add Variable
	// 2�������W
	FIntPoint Coordinate2D;
};
