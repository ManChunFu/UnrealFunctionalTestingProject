// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	MoveXAxis,
	MoveYAxis,
	MoveZAxis
};

UCLASS()
class FIRSTPROJECTUDEMY_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovingPlatform")
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovingPlatform")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform")
	FVector EndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform")
	float MovingRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform")
	float MovingLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform")
	bool bIsMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovingPlatform")
	EAIState MovingDirectionState;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	UFUNCTION(BlueprintCallable)
	void OverlapBoxComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle MoveTimerHandle;
	void MovePlatform();

private:
	bool bIsArrivedToDestination;
	FVector DefaultLocation;
};
