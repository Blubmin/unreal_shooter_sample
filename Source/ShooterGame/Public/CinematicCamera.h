// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneCaptureComponent2D.h"
#include "ShooterGame.h"
#include "CinematicCamera.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class SHOOTERGAME_API UCinematicCamera : public USceneCaptureComponent2D
{
	GENERATED_BODY()

public:
	UCinematicCamera(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void Update(const TArray<AShooterCharacter*>& candidates);
};
