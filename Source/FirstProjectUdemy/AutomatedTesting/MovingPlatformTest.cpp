// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Tests/AutomationCommon.h"
#include "AssetSelection.h"
#include "../MovingPlatform.h"
#include "TimerManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AMovingPlatformTest, "AMovingPlatformTest.Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool AMovingPlatformTest::RunTest(const FString& Paramters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	AMovingPlatform* MovingPlatform = World->SpawnActor<AMovingPlatform>(FVector(0.0f), FRotator(0.0f));
	MovingPlatform->StartLocation = FVector(0.0f);
	MovingPlatform->EndLocation = FVector(20.0f, 20.0f, 20.0f);
	MovingPlatform->bIsMoving = true;
	TestNotNull("World is created", GWorld.GetReference());
	TestNotNull("MovingPlatform is spawned", MovingPlatform);
	TestEqual("MovingPlatform should move to FVector (20.0f, 20.0f, 20.0f)", MovingPlatform->GetActorLocation(), MovingPlatform->EndLocation);
	
	return true;
}

