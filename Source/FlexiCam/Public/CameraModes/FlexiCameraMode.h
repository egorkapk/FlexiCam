// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"

#include "FlexiCameraMode.generated.h"

#define UE_API FLEXICAM_API

class AActor;
class UFlexiCameraComponent;

/**
 * ECameraModeBlendFunction
 *
 *	Blend function used for transitioning between camera modes.
 */
UENUM(BlueprintType)
enum class ECameraModeBlendFunction : uint8
{
	// Does a simple linear interpolation.
	Linear,

	// Immediately accelerates, but smoothly decelerates into the target.  Ease amount controlled by the exponent.
	EaseIn,

	// Smoothly accelerates, but does not decelerate into the target.  Ease amount controlled by the exponent.
	EaseOut,

	// Smoothly accelerates and decelerates.  Ease amount controlled by the exponent.
	EaseInOut,

	COUNT	UMETA(Hidden)
};

/**
 * FCameraModeView
 *
 *	View data produced by the camera mode that is used to blend camera modes.
 */
struct FFlexiCameraModeView
{
public:

	FFlexiCameraModeView();

	void Blend(const FFlexiCameraModeView& Other, float OtherWeight);

public:

	FVector Location;
	FRotator Rotation;
	FRotator ControlRotation;
	float FieldOfView;
};


/**
 * Base class for all FlexiCam camera modes
 */
UCLASS(MinimalAPI, Abstract, Blueprintable)
class UFlexiCameraMode : public UObject
{
	GENERATED_BODY()

public:

	UE_API UFlexiCameraMode();
	UE_API UFlexiCameraComponent* GetFlexiCameraComponent() const;
	UE_API virtual UWorld* GetWorld() const override;
	UE_API AActor* GetTargetActor() const;
	UE_API void UpdateCameraMode(float DeltaTime);
	UE_API void SetBlendWeight(float Weight);

public:
	// Called when this camera mode is activated on the camera mode stack.
	virtual void OnActivation() {};
	// Called when this camera mode is deactivated on the camera mode stack.
	virtual void OnDeactivation() {};

	const FFlexiCameraModeView& GetCameraModeView() const;
	float GetBlendTime() const;
	float GetBlendWeight() const;
	FGameplayTag GetCameraTypeTag() const;

protected:

	UE_API virtual FVector GetPivotLocation() const;
	UE_API virtual FRotator GetPivotRotation() const;

	UE_API virtual void UpdateView(float DeltaTime);
	UE_API virtual void UpdateBlending(float DeltaTime);

protected:
	// A tag that can be queried by gameplay code that cares when a kind of camera mode is active
	// without having to ask about a specific mode.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	FGameplayTag CameraTypeTag;

	// View output produced by the camera mode.
	FFlexiCameraModeView View;

	// The horizontal field of view (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "5.0", UIMax = "170", ClampMin = "5.0", ClampMax = "170.0"))
	float FieldOfView;

	// Minimum view pitch (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMin;

	// Maximum view pitch (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMax;

	// How long it takes to blend in this mode.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendTime;

	// Function used for blending.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	ECameraModeBlendFunction BlendFunction;

	// Exponent used by blend functions to control the shape of the curve.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendExponent;

	// Linear blend alpha used to determine the blend weight.
	float BlendAlpha;

	// Blend weight calculated using the blend alpha and function.
	float BlendWeight;

protected:
	/** If true, skips all interpolation and puts camera in ideal location.  Automatically set to false next frame. */
	UPROPERTY(transient)
	uint32 bResetInterpolation : 1;
};


/**
 * UFlexiCameraModeStack
 *
 *	Stack used for blending camera modes.
 */
UCLASS()
class UFlexiCameraModeStack : public UObject
{
	GENERATED_BODY()

public:

	UFlexiCameraModeStack();

	void ActivateStack();
	void DeactivateStack();

	bool IsStackActivate() const { return bIsActive; }

	void PushCameraMode(TSubclassOf<UFlexiCameraMode> CameraModeClass);

	bool EvaluateStack(float DeltaTime, FFlexiCameraModeView& OutCameraModeView);

	// Gets the tag associated with the top layer and the blend weight of it
	void GetBlendInfo(float& OutWeightOfTopLayer, FGameplayTag& OutTagOfTopLayer) const;

protected:

	UFlexiCameraMode* GetCameraModeInstance(TSubclassOf<UFlexiCameraMode> CameraModeClass);

	void UpdateStack(float DeltaTime);
	void BlendStack(FFlexiCameraModeView& OutCameraModeView) const;

protected:

	bool bIsActive;

	UPROPERTY()
	TArray<TObjectPtr<UFlexiCameraMode>> CameraModeInstances;

	UPROPERTY()
	TArray<TObjectPtr<UFlexiCameraMode>> CameraModeStack;
};

//#undef UE_API