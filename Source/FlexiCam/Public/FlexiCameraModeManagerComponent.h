// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlexiCameraModeManagerComponent.generated.h"


class UFlexiCameraMode;
class UFlexiCameraComponent;

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
