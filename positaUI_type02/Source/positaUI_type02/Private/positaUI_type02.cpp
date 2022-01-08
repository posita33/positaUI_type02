// Copyright Epic Games, Inc. All Rights Reserved.

#include "positaUI_type02.h"
#include "positaUI_type02Style.h"
#include "positaUI_type02Commands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "ToolMenus.h"

#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"

static const FName positaUI_type02TabName("positaUI_type02");

#define LOCTEXT_NAMESPACE "FpositaUI_type02Module"

void FpositaUI_type02Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FpositaUI_type02Style::Initialize();
	FpositaUI_type02Style::ReloadTextures();

	FpositaUI_type02Commands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FpositaUI_type02Commands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FpositaUI_type02Module::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FpositaUI_type02Module::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(positaUI_type02TabName, FOnSpawnTab::CreateRaw(this, &FpositaUI_type02Module::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FpositaUI_type02TabTitle", "positaUI_type02"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FpositaUI_type02Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FpositaUI_type02Style::Shutdown();

	FpositaUI_type02Commands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(positaUI_type02TabName);
}

TSharedRef<SDockTab> FpositaUI_type02Module::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FpositaUI_type02Module::OnSpawnPluginTab")),
		FText::FromString(TEXT("positaUI_type02.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(10.0f, 3.0f, 10.0f, 3.0f)
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(SButton)
						.Text(LOCTEXT("Coordinate_Button", "Coordinate"))
						.OnClicked_Raw(this, &FpositaUI_type02Module::CoordinateButtonClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(0.0f, 3.0f, 8.0f, 3.0f)
					[
						SNew(SNumericEntryBox<int32>)
						.IsEnabled(true)
						.AllowSpin(true)
						.MinSliderValue(-10000)
						.MaxSliderValue(10000)
						.Value_Raw(this, &FpositaUI_type02Module::GetCoordinate2DX)
						.OnValueChanged_Raw(this, &FpositaUI_type02Module::SetCoordinate2DX)
						.OnValueCommitted_Raw(this, &FpositaUI_type02Module::SetCoordinate2DXCommit)
						.AllowSpin(true)
						.MinDesiredValueWidth(75)
						.Label()
						[
							SNew(SBox)
							.VAlign(VAlign_Center)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("Coordinate2D_X", "X"))
							]
						]
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(0.0f, 3.0f, 8.0f, 3.0f)
					[
						SNew(SNumericEntryBox<int32>)
						.IsEnabled(true)
						.AllowSpin(true)
						.MinSliderValue(-10000)
						.MaxSliderValue(10000)
						.Value_Raw(this, &FpositaUI_type02Module::GetCoordinate2DY)
						.OnValueChanged_Raw(this, &FpositaUI_type02Module::SetCoordinate2DY)
						.OnValueCommitted_Raw(this, &FpositaUI_type02Module::SetCoordinate2DYCommit)
						.AllowSpin(true)
						.MinDesiredValueWidth(75)
						.Label()
						[
							SNew(SBox)
							.VAlign(VAlign_Center)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("Coordinate2D_Y", "Y"))
							]
						]
					]
				]
			]
		];
}

void FpositaUI_type02Module::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(positaUI_type02TabName);
}

void FpositaUI_type02Module::SetCoordinate2DX(int32 NewValue)
{
	Coordinate2D.X = NewValue;
}

void FpositaUI_type02Module::SetCoordinate2DXCommit(int32 NewValue, ETextCommit::Type)
{
	SetCoordinate2DX(NewValue);
}

void FpositaUI_type02Module::SetCoordinate2DY(int32 NewValue)
{
	Coordinate2D.Y = NewValue;
}

void FpositaUI_type02Module::SetCoordinate2DYCommit(int32 NewValue, ETextCommit::Type)
{
	SetCoordinate2DY(NewValue);
}

FReply FpositaUI_type02Module::CoordinateButtonClicked()
{
	UWorld* world = GEditor->GetEditorWorldContext().World();
	for (TActorIterator<AStaticMeshActor> actorItr(world); actorItr; ++actorItr)
	{
		FString staticMeshName = actorItr->GetActorLabel();
		if (staticMeshName.Equals(TEXT("Floor")))
			actorItr->SetActorLocation(FVector(Coordinate2D.X, Coordinate2D.Y, actorItr->GetActorLocation().Z));
	}
	return FReply::Handled();
}

void FpositaUI_type02Module::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FpositaUI_type02Commands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FpositaUI_type02Commands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FpositaUI_type02Module, positaUI_type02)