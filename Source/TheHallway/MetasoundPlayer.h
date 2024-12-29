// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "SplineActor.h"
#include "MetasoundPlayer.generated.h"

UCLASS()
class THEHALLWAY_API AMetasoundPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetasoundPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAudioComponent* Metasound;

	UPROPERTY(EditAnywhere)
	ASplineActor* Spline;

	float SplineValue;
};
