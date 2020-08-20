// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySessionFrontend.h"
#include "Tests/AutomationEditorCommon.h"
#include "Tests/AutomationCommon.h"
#include "AssetSelection.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AEnemyTest, "AEnemyTest.Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool AEnemyTest::RunTest(const FString& Paramters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	AEnemy* Enemy = World->SpawnActor<AEnemy>(FVector(0.0f), FRotator(0.0f));
	EEnemyMovementStatus EnemyMovementStatus = EEnemyMovementStatus::EMS_Idle;
	Enemy->SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
	TestNotNull("World is created", GWorld.GetReference());
	TestNotNull("Enemy is spawned", Enemy);
	TestEqual("EnemyMovementStatus should equal EEnemyMovementStatus::EMS_Attacking ", Enemy->EnemyMovementStatus, EEnemyMovementStatus::EMS_Attacking);
	
	return true;
}

