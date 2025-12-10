// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/TopDownCameraModeTrigger.h"

#include "Examples/TopDownCameraMode.h"

ATopDownCameraModeTrigger::ATopDownCameraModeTrigger()
{
	CameraModeClass = UTopDownCameraMode::StaticClass();
}

UBoxComponent* ATopDownCameraModeTrigger::GetTriggerVolume() const
{
	if (TriggerVolume)
	{
		return TriggerVolume;
	}
	return nullptr;
}
