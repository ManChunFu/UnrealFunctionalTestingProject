// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetSimulatePhysics(false);
	BoxComp->SetEnableGravity(false);
	RootComponent = BoxComp;
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OverlapBoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(false);
	MeshComp->SetEnableGravity(false);
	MeshComp->SetupAttachment(BoxComp);

	StartLocation = FVector(0.0f);
	EndLocation = FVector(0.0f);

	MovingRate = 0.001f;
	MovingLength = 0.5f;
	bIsMoving = false;
	bIsArrivedToDestination = false;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->SetRelativeLocation(StartLocation);
	DefaultLocation = StartLocation;

	if (FMath::Abs(EndLocation.X - StartLocation.X) > 0)
	{
		MovingDirectionState = EAIState::MoveXAxis;
	}

	if (FMath::Abs(EndLocation.Y - StartLocation.Y) > 0)
	{
		MovingDirectionState = EAIState::MoveYAxis;
	}

	if (FMath::Abs(EndLocation.Z - StartLocation.Z) > 0)
	{
		MovingDirectionState = EAIState::MoveZAxis;
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		MovePlatform();
	}

}

void AMovingPlatform::OverlapBoxComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<UCapsuleComponent>(OtherComp))
	{
		if (OtherActor)
		{
			GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &AMovingPlatform::MovePlatform, MovingRate, true);
			bIsMoving = true;
			bIsArrivedToDestination = false;
		}
	}
}

void AMovingPlatform::MovePlatform()
{
	if (bIsMoving)
	{
		FVector CurrentLocation = BoxComp->GetRelativeLocation();

		if ((CurrentLocation - EndLocation).Size() < 0.5f)
		{
			GetWorldTimerManager().PauseTimer(MoveTimerHandle);
			bIsMoving = false;
			BoxComp->SetRelativeLocation(EndLocation);
			EndLocation = StartLocation;
			StartLocation = CurrentLocation;
			bIsArrivedToDestination = true;
			return;
		}

		FVector NewLocation;
		switch (MovingDirectionState)
		{
		case EAIState::MoveXAxis:
			if (CurrentLocation.X < EndLocation.X)
			{
				NewLocation = { CurrentLocation.X + MovingLength, CurrentLocation.Y, CurrentLocation.Z };
			}
			else
			{
				NewLocation = { CurrentLocation.X - MovingLength, CurrentLocation.Y, CurrentLocation.Z };
			}
			break;
		case EAIState::MoveYAxis:
			if (CurrentLocation.Y < EndLocation.Y)
			{
				NewLocation = { CurrentLocation.X, CurrentLocation.Y + MovingLength, CurrentLocation.Z };
			}
			else
			{
				NewLocation = { CurrentLocation.X, CurrentLocation.Y - MovingLength, CurrentLocation.Z };

			}
			break;
		case EAIState::MoveZAxis:
			if (CurrentLocation.Z < EndLocation.Z)
			{
				NewLocation = { CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + MovingLength };
			}
			else
			{
				NewLocation = { CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z - MovingLength };
			}
			break;
		default:
			break;
		}
		BoxComp->SetRelativeLocation(NewLocation);
	}
}



