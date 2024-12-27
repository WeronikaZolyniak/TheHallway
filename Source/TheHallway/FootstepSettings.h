// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FootstepSettings.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class THEHALLWAY_API UFootstepSettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TMap<UPhysicalMaterial*, USoundBase*> FootstepMapping;
};
