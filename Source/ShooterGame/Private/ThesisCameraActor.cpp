// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "ThesisCameraActor.h"

AThesisCameraActor::AThesisCameraActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	Target = TWeakObjectPtr<AShooterCharacter>(nullptr);
}