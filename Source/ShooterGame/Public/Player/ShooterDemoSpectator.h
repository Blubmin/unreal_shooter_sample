// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ShooterDemoSpectator.generated.h"

class SShooterDemoHUD;
class ACinematicCamera;
class APlayerCamera;
class AThesisCameraActor;

UCLASS(config=Game)
class AShooterDemoSpectator : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:
	/** shooter in-game menu */
	TSharedPtr<class FShooterDemoPlaybackMenu> ShooterDemoPlaybackMenu;

	virtual void SetupInputComponent() override;
	virtual void SetPlayer( UPlayer* Player ) override;
	virtual void Destroyed() override;
	virtual void Tick(float DeltaSeconds) override;

	void OnToggleInGameMenu();
	void OnIncreasePlaybackSpeed();
	void OnDecreasePlaybackSpeed();
	void SetCameraPlayer(int NewIndex);
	void OnNextPlayer();
	void OnPrevPlayer();
	void OnSwitchCamera();

	int32 PlaybackSpeed;

private:
	TSharedPtr<SShooterDemoHUD> DemoHUD;

	int PlayerIdx;
	AThesisCameraActor* Camera;
	ACinematicCamera* CinematicCamera;
	APlayerCamera* PlayerCamera;
};

