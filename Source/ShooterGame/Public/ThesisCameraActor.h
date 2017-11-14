// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "ThesisCameraActor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class SHOOTERGAME_API AThesisCameraActor : public ACameraActor
{
	GENERATED_BODY()

protected:
	TWeakObjectPtr<AShooterCharacter> Target;

public:
	AThesisCameraActor(const FObjectInitializer& ObjectInitializer);
	virtual void SetPlayer(TWeakObjectPtr<AShooterCharacter> NewTarget) {};
};
