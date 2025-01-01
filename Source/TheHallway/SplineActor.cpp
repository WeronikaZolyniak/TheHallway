// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineActor.h"
#include "Kismet/GameplayStatics.h"
#include "TheHallwayCharacter.h"

// Sets default values
ASplineActor::ASplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;
	Spline->SetDrawDebug(true);

	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
}

// Called when the game starts or when spawned
void ASplineActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Sound->SetFloatParameter(NameOfParameterToModify, GetPlayersDistanceAlongSpline());
}

float ASplineActor::GetPlayersDistanceAlongSpline()
{
	float SplineLength = Spline->GetSplineLength();
	float ClosestInputKey = Spline->FindInputKeyClosestToWorldLocation(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
	float DistanceAlongSpline = Spline->GetDistanceAlongSplineAtSplineInputKey(ClosestInputKey);

	float PercentageAlongSpline = DistanceAlongSpline / SplineLength;
	return PercentageAlongSpline;
}

