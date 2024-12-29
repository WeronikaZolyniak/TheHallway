// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "FootstepSettings.generated.h"

UCLASS(EditInlineNew, DefaultToInstanced, CollapseCategories)
class THEHALLWAY_API UFootstepSettings : public UObject
{
	GENERATED_BODY()

public:
	UFootstepSettings() {};

	UPROPERTY(EditAnywhere)
	TMap<UPhysicalMaterial*, USoundBase*> FootstepMapping;
};
