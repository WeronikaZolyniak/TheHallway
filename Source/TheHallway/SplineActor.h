// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/AudioComponent.h"
#include "SplineActor.generated.h"

UCLASS()
class THEHALLWAY_API ASplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USplineComponent* Spline;

	float GetPlayersDistanceAlongSpline();

	UPROPERTY(EditAnywhere)
	UAudioComponent* Sound;

	UPROPERTY(EditAnywhere)
	FName NameOfParameterToModify;
};
