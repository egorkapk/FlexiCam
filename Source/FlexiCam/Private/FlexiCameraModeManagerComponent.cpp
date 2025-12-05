// Fill out your copyright notice in the Description page of Project Settings.


#include "FlexiCameraModeManagerComponent.h"

#include "FlexiCameraComponent.h"
#include "CameraModes/FlexiCameraMode.h"

// Sets default values for this component's properties
UFlexiCameraModeManagerComponent::UFlexiCameraModeManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultCameraModeClass = nullptr;
	CurrentCameraModeClass = nullptr;
}

// Called when the game starts
void UFlexiCameraModeManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UFlexiCameraComponent* CameraComponent = UFlexiCameraComponent::FindCameraComponent(GetOwner()))
	{
		CameraComponent->DetermineCameraModeDelegate.BindUObject(this, &ThisClass::DetermineCameraMode);
	}
}

void UFlexiCameraModeManagerComponent::SetCameraMode(TSubclassOf<UFlexiCameraMode> NewCameraModeClass)
{
	if (NewCameraModeClass)
	{
		CurrentCameraModeClass = NewCameraModeClass;
	}
}

void UFlexiCameraModeManagerComponent::ResetToDefaultCameraMode()
{
	CurrentCameraModeClass = nullptr;
}

TSubclassOf<UFlexiCameraMode> UFlexiCameraModeManagerComponent::DetermineCameraMode() const
{
	if (CurrentCameraModeClass)
	{
		return CurrentCameraModeClass;
	}
	return DefaultCameraModeClass;
}
