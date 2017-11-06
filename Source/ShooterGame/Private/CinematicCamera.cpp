// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "CinematicCamera.h"

UCinematicCamera::UCinematicCamera(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) {
	//bCaptureEveryFrame = false;
	//bCaptureOnMovement = false;

	//TextureTarget = ObjectInitializer.CreateDefaultSubobject<UTextureRenderTarget2D>(this, TEXT("TextureTarget"));
	//TextureTarget->bHDR = true;
	//TextureTarget->TargetGamma = 1.f;
	//TextureTarget->ClearColor = FLinearColor::Black;
	//TextureTarget->InitAutoFormat(1024, 1024);
}

void UCinematicCamera::Init() {
	//bCaptureEveryFrame = true;
	//bCaptureOnMovement = true;
	//bEnableClipPlane = true;
	//bUseCustomProjectionMatrix = true;
	//FOVAngle = 90.f;
	//ProjectionType = ECameraProjectionMode::Perspective;
	//FVector2D viewportsSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	//CustomProjectionMatrix = FPerspectiveMatrix(90, 1, viewportsSize.X / viewportsSize.Y, 1, 10000);
	//TextureTarget->InitAutoFormat(1024, 1024);
}

void UCinematicCamera::Update(const TArray<AShooterCharacter*>& candidates) {
	for (auto& candidate : candidates) {
		TArray<FVector> positions;
		candidate->GetPositions(positions);
		UE_LOG(LogTemp, Log, TEXT("Num Verts: %d"), positions.Num());
	}
}