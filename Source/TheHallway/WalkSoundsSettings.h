// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Sound/SoundWave.h"
#include "WalkSoundsSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Walk Sounds"))
class THEHALLWAY_API UWalkSoundsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(config, EditAnywhere)
	TMap<FString, FSoftObjectPath> PhysicalMatNameAndSound;
};
