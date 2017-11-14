// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "PlayerCamera.h"


APlayerCamera::APlayerCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCamera::SetPlayer(TWeakObjectPtr<AShooterCharacter> NewTarget) {
	if (Target.IsValid()) Target->SwapMesh();
	Target = TWeakObjectPtr<AShooterCharacter>(NewTarget.Get());
	if (Target.IsValid()) Target->SwapMesh();
}

void APlayerCamera::Tick(float DeltaTime) {
	if (!Target.IsValid()) {
		UE_LOG(LogTemp, Log, TEXT("INVALID"));
		return;
	};
	FVector position;
	FRotator rotation;
	Target->GetActorEyesViewPoint(position, rotation);
	GetCameraComponent()->SetRelativeLocationAndRotation(position, rotation);
}