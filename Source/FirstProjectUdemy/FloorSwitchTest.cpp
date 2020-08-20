// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitchTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Tests/AutomationCommon.h"
#include "AssetSelection.h"
#include "FloorSwitch.h"
#include "MainCharacter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AFloorSwitchTest, "AFloorSwitchTest.Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool AFloorSwitchTest::RunTest(const FString& Paramters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	AFloorSwitch* FloorSwitch = World->SpawnActor<AFloorSwitch>(FVector(0.0f), FRotator(0.0f));
	AMainCharacter* MainCharacter = World->SpawnActor<AMainCharacter>(FVector(0.0f, 0.0f, 30.0f), FRotator(0.0f));

	TestNotNull("World is created", GWorld.GetReference());
	TestNotNull("Enemy is spawned", MainCharacter);
	return true;
}


