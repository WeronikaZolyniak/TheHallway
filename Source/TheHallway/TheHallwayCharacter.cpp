// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheHallwayCharacter.h"
#include "TheHallwayProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "WalkSoundsSettings.h"
#include "FootstepSettings.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheHallwayCharacter

ATheHallwayCharacter::ATheHallwayCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	StepSoundLinetraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("StepSoundLinetraceStart"));
	StepSoundLinetraceStart->SetupAttachment(RootComponent);

}

void ATheHallwayCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//GetDistanceAlongSpline();
}

void ATheHallwayCharacter::BeginPlay()
{
	Super::BeginPlay();


}

//////////////////////////////////////////////////////////////////////////// Input

void ATheHallwayCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATheHallwayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheHallwayCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ATheHallwayCharacter::StopMoving);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheHallwayCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ATheHallwayCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		IsMoving = true;

		float LocationDifference = MovementVector.Length();

		if (DistanceSinceFootstepSound + LocationDifference >= DistanceBetweenFootstepSoundsInCm)
		{
			DistanceSinceFootstepSound = 0;
			PlayWalkSound();
		}
		else
		{
			DistanceSinceFootstepSound += LocationDifference;
		}
		
	}
}

void ATheHallwayCharacter::StopMoving(const FInputActionValue& Value)
{
	IsMoving = false;
}

void ATheHallwayCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATheHallwayCharacter::PlayWalkSound()
{
	UE_LOG(LogTemp, Error, TEXT("Sound"));
	//check if moving
	/*if (!IsMoving)
	{
		StepSoundFinished = true;
		return;
	}

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.bReturnPhysicalMaterial = true;

	bool FloorDetected = GetWorld()->LineTraceSingleByChannel(
		Hit,
		StepSoundLinetraceStart->GetComponentLocation(),
		StepSoundLinetraceStart->GetComponentLocation() + FVector(0,0,-100),
		ECollisionChannel::ECC_Visibility, Params);


	//DrawDebugLine(GetWorld(), StepSoundLinetraceStart->GetComponentLocation(), StepSoundLinetraceStart->GetComponentLocation() + FVector(0, 0, -100), FColor::Green, true);

	if (FloorDetected)
	{
		TWeakObjectPtr <UPhysicalMaterial> HitMaterial = Hit.PhysMaterial;
		UPhysicalMaterial* HitMaterialPointer = Cast<UPhysicalMaterial>(HitMaterial);

		const UWalkSoundsSettings* WalkSoundsSetting = GetDefault<UWalkSoundsSettings>();
		check(WalkSoundsSetting); //unreal's assert

		FSoftObjectPath path = WalkSoundsSetting->FootstepMapping;
		//*static UObject* FootstepsSettingObj = path.TryLoad();
		//check(FootstepsSettingObj);
		//TSubclassOf<UObject> clas = FootstepsSettingObj->GetClass();
		//FName ClassName = FootstepsSettingObj->GetClass()->GetFName();
		
		UFootstepSettings* FootstepSettings = (UFootstepSettings*)path.TryLoad();
		//UFootstepSettings* FootstepSettings = Cast<UFootstepSettings>(path.TryLoad());
		check(FootstepSettings);

		//TMap<UPhysicalMaterial*, USoundBase*> FootstepMapping = FootstepSettings->FootstepMapping;

		USoundBase* FootstepSound = *FootstepSettings->FootstepMapping.Find(HitMaterialPointer);

		if (FootstepSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootstepSound, StepSoundLinetraceStart->GetComponentLocation());
		}
		
	}*/
}

//percents: from 0 to 1
float ATheHallwayCharacter::GetDistanceAlongSpline(TSoftObjectPtr<ASplineActor> SplineActor)
{
	if (!SplineActor) return -1;

	USplineComponent* Spline = SplineActor->Spline;

	float SplineLength = Spline->GetSplineLength();

	float ClosestInputKey = Spline->FindInputKeyClosestToWorldLocation(GetActorLocation());
	float DistanceAlongSpline = Spline->GetDistanceAlongSplineAtSplineInputKey(ClosestInputKey);


	float PercentageAlongSpline = DistanceAlongSpline / SplineLength;
	return PercentageAlongSpline;
}
