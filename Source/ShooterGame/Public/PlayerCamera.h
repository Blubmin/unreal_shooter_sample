// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ThesisCameraActor.h"
#include "PlayerCamera.generated.h"

/**
*
*/
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class SHOOTERGAME_API APlayerCamera : public AThesisCameraActor {

	GENERATED_UCLASS_BODY()

public:
	virtual void SetPlayer(TWeakObjectPtr<AShooterCharacter> NewTarget) override;
	virtual void Tick(float DeltaTime) override;
};