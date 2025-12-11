// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlexiCameraModeManagerComponent.generated.h"


class UFlexiCameraMode;
class UFlexiCameraComponent;
struct FGameplayTagContainer;

/**
* Component to manage CameraModes
**/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLEXICAM_API UFlexiCameraModeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlexiCameraModeManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "FlexiCam|Modes")
	void SetCameraMode(TSubclassOf<UFlexiCameraMode> NewCameraModeClass);

	UFUNCTION(BlueprintCallable, Category = "FlexiCam|Modes")
	void ResetToDefaultCameraMode();

	// Gets the tag associated with the current camera mode and the blend weight of it
	UFUNCTION(BlueprintCallable, Category = "FlexiCam|Modes")
	void GetCurrentCameraModeBlendInfo(float& OutWeightOfTopLayer, FGameplayTagContainer& OutTagsOfTopLayer) const;

	// Return true if CurrentCameraMode has any of provided tags
	UFUNCTION(BlueprintCallable, Category = "FlexiCam|Modes")
	bool CurrentCameraModeHasAnyTag(const FGameplayTagContainer& ContainerToCheck);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Determines the appropriate camera mode class to use.
	TSubclassOf<UFlexiCameraMode> DetermineCameraMode() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FlexiCam|Modes")
	TSubclassOf<UFlexiCameraMode> DefaultCameraModeClass;

private:
	TSubclassOf<UFlexiCameraMode> CurrentCameraModeClass;
};
