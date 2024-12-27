// Fill out your copyright notice in the Description page of Project Settings.


#include "MetasoundPlayer.h"

// Sets default values
AMetasoundPlayer::AMetasoundPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Metasound = CreateDefaultSubobject<UAudioComponent>(TEXT("Metasound"));
	Metasound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AMetasoundPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMetasoundPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

