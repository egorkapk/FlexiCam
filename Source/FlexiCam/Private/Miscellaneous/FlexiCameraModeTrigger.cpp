// Fill out your copyright notice in the Description page of Project Settings.


#include "Miscellaneous/FlexiCameraModeTrigger.h"

#include "Components/BoxComponent.h"
#include "FlexiCameraModeManagerComponent.h"
#include "FlexiCamInterface.h"

// Sets default values
AFlexiCameraModeTrigger::AFlexiCameraModeTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	check(TriggerVolume);
	RootComponent = TriggerVolume;
	TriggerVolume->SetGenerateOverlapEvents(true);
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AFlexiCameraModeTrigger::OnTriggerBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AFlexiCameraModeTrigger::OnTriggerEndOverlap);
}

void AFlexiCameraModeTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UFlexiCameraModeManagerComponent* CameraModeManagerComponent = GetCameraModeManagerComponent(OtherActor))
	{
		CameraModeManagerComponent->SetCameraMode(CameraModeClass);
	}
}

void AFlexiCameraModeTrigger::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UFlexiCameraModeManagerComponent* CameraModeManagerComponent = GetCameraModeManagerComponent(OtherActor))
	{
		CameraModeManagerComponent->ResetToDefaultCameraMode();
	}
}

UFlexiCameraModeManagerComponent* AFlexiCameraModeTrigger::GetCameraModeManagerComponent(AActor* Actor) const
{
	if (!Actor)
	{
		return nullptr;
	}
	if (IFlexiCamInterface* FlexiCamInterface = Cast<IFlexiCamInterface>(Actor))
	{
		return FlexiCamInterface->GetFlexiCameraModeManagerComponent();
	}
	return nullptr;
}
