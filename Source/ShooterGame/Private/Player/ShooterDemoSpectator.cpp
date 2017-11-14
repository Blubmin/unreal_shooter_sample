// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Player/ShooterDemoSpectator.h"
#include "UI/Menu/ShooterDemoPlaybackMenu.h"
#include "UI/Widgets/SShooterDemoHUD.h"
#include "Engine/DemoNetDriver.h"
<<<<<<< HEAD
#include "ThesisCameraActor.h"
#include "CinematicCamera.h"
#include "PlayerCamera.h"
=======
>>>>>>> 51c9672575e3eda7f4e5cb86d69c1bfbf34462ab

AShooterDemoSpectator::AShooterDemoSpectator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
	bShouldPerformFullTickWhenPaused = true;

	PlayerIdx = -1;
	CinematicCamera = ObjectInitializer.CreateDefaultSubobject<ACinematicCamera>(this, TEXT("CinematicCamera"));
	PlayerCamera = ObjectInitializer.CreateDefaultSubobject<APlayerCamera>(this, TEXT("PlayerCamera"));
	Camera = PlayerCamera;
}

void AShooterDemoSpectator::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UI input
	InputComponent->BindAction( "InGameMenu", IE_Pressed, this, &AShooterDemoSpectator::OnToggleInGameMenu );

	InputComponent->BindAction( "NextWeapon", IE_Pressed, this, &AShooterDemoSpectator::OnIncreasePlaybackSpeed );
	InputComponent->BindAction( "PrevWeapon", IE_Pressed, this, &AShooterDemoSpectator::OnDecreasePlaybackSpeed );
	InputComponent->BindAction("NextPlayer", IE_Pressed, this, &AShooterDemoSpectator::OnNextPlayer);
	InputComponent->BindAction("PrevPlayer", IE_Pressed, this, &AShooterDemoSpectator::OnPrevPlayer);
	InputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AShooterDemoSpectator::OnSwitchCamera);
}

void AShooterDemoSpectator::SetPlayer( UPlayer* InPlayer )
{
	Super::SetPlayer( InPlayer );
	SetViewTarget(Camera);

	// Build menu only after game is initialized
	ShooterDemoPlaybackMenu = MakeShareable( new FShooterDemoPlaybackMenu() );
	ShooterDemoPlaybackMenu->Construct( Cast< ULocalPlayer >( Player ) );

	// Create HUD if this is playback
	if (GetWorld() != nullptr && GetWorld()->DemoNetDriver != nullptr && !GetWorld()->DemoNetDriver->IsServer())
	{
		if (GEngine != nullptr && GEngine->GameViewport != nullptr)
		{
			DemoHUD = SNew(SShooterDemoHUD)
				.PlayerOwner(this);

			GEngine->GameViewport->AddViewportWidgetContent(DemoHUD.ToSharedRef());
		}
	}

	FActorSpawnParameters SpawnInfo;

	SpawnInfo.Owner				= this;
	SpawnInfo.Instigator		= Instigator;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PlaybackSpeed = 2;

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(DemoHUD);

	SetInputMode(InputMode);
}

void AShooterDemoSpectator::OnToggleInGameMenu()
{
	// if no one's paused, pause
	if ( ShooterDemoPlaybackMenu.IsValid() )
	{
		ShooterDemoPlaybackMenu->ToggleGameMenu();
	}
}

static float PlaybackSpeedLUT[5] = { 0.1f, 0.5f, 1.0f, 2.0f, 4.0f };

void AShooterDemoSpectator::OnIncreasePlaybackSpeed()
{
	PlaybackSpeed = FMath::Clamp( PlaybackSpeed + 1, 0, 4 );

	GetWorldSettings()->DemoPlayTimeDilation = PlaybackSpeedLUT[ PlaybackSpeed ];
}

void AShooterDemoSpectator::OnDecreasePlaybackSpeed()
{
	PlaybackSpeed = FMath::Clamp( PlaybackSpeed - 1, 0, 4 );

	GetWorldSettings()->DemoPlayTimeDilation = PlaybackSpeedLUT[ PlaybackSpeed ];
}

void AShooterDemoSpectator::SetCameraPlayer(int NewIndex) {
	UWorld* world = GetWorld();
	if (!world) {
		UE_LOG(LogTemp, Log, TEXT("NO WORLD AHHH"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Start"));
	TArray<AActor*> ShooterCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterCharacter::StaticClass(), ShooterCharacters);
	UE_LOG(LogTemp, Log, TEXT("Array"));
	if (ShooterCharacters.Num() == 0) return;
	UE_LOG(LogTemp, Log, TEXT("Idx"));
	PlayerIdx = ((NewIndex % ShooterCharacters.Num()) + ShooterCharacters.Num()) % ShooterCharacters.Num();

	UE_LOG(LogTemp, Log, TEXT("Cinematic"));
	CinematicCamera->SetPlayer(TWeakObjectPtr<AShooterCharacter>(Cast<AShooterCharacter>(ShooterCharacters[PlayerIdx])));
	UE_LOG(LogTemp, Log, TEXT("PLayer"));
	PlayerCamera->SetPlayer(TWeakObjectPtr<AShooterCharacter>(Cast<AShooterCharacter>(ShooterCharacters[PlayerIdx])));
	UE_LOG(LogTemp, Log, TEXT("Done"));
}

void AShooterDemoSpectator::OnNextPlayer() {
	SetCameraPlayer(PlayerIdx + 1);
}

void AShooterDemoSpectator::OnPrevPlayer() {
	SetCameraPlayer(PlayerIdx - 1);
}

void AShooterDemoSpectator::Destroyed()
{
	if (GEngine != nullptr && GEngine->GameViewport != nullptr && DemoHUD.IsValid())
	{
		// Remove HUD
		GEngine->GameViewport->RemoveViewportWidgetContent(DemoHUD.ToSharedRef());
	}

	Super::Destroyed();
}

void AShooterDemoSpectator::Tick(float DeltaSeconds) {
	Camera->Tick(DeltaSeconds);
}

void AShooterDemoSpectator::OnSwitchCamera() {
	UE_LOG(LogTemp, Log, TEXT("SWAP")); 
	if (Camera == PlayerCamera) Camera = CinematicCamera;
	else Camera = PlayerCamera;
	SetViewTarget(Camera);
}
