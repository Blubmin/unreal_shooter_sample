// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "CinematicCamera.h"
#include "EngineUtils.h"

ACinematicCamera::ACinematicCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
}

void ACinematicCamera::SetPlayer(TWeakObjectPtr<AShooterCharacter> NewTarget) {
	Target = TWeakObjectPtr<AShooterCharacter>(NewTarget.Get());
}

void ACinematicCamera::Tick(float DeltaTime) {
	if (!Target.IsValid()) {
		UE_LOG(LogTemp, Log, TEXT("INVALID"));
		return;
	};
	FVector position;
	FRotator rotation;
	Target->GetActorEyesViewPoint(position, rotation);
	GetCameraComponent()->SetRelativeLocationAndRotation(position, rotation);
}