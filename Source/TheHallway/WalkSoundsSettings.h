// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Sound/SoundBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "WalkSoundsSettings.generated.h"

/*UCLASS(BlueprintType, Blueprintable)
class THEHALLWAY_API UFootstepsSettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TMap<UPhysicalMaterial*, USoundBase*> FootstepMapping;
};*/

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Walk Sounds"))
class THEHALLWAY_API UWalkSoundsSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere) //meta = (AllowedTypes = "FootstepsSettings"))
	FSoftObjectPath FootstepMapping;
};
