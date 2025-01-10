// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PongGameMode.h"

#include "Camera/PongCamera.h"
#include "Controllers/PongPlayerController.h"
#include "Gameplay/Background.h"
#include "Gameplay/PongBall.h"
#include "Gameplay/PongBounds.h"
#include "Gameplay/PongPaddle.h"

APongGameMode::APongGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = APongPlayerController::StaticClass();
	DefaultPawnClass = APongPaddle::StaticClass();
}

void APongGameMode::StartPlay()
{
	Super::StartPlay();
	UWorld* const World = GetWorld();
	if(World)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		APongCamera* PongCamera = World->SpawnActor<APongCamera>(APongCamera::StaticClass(),SpawnParameters);
		
		if(!ensure(PongCamera))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn PongCamera"));
			return;
		}
		
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (!ensure(PlayerController))
		{
		    UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController"));
		    return;
		}
		PlayerController->SetViewTarget(PongCamera);
		
		ABackground* Background = World->SpawnActor<ABackground>(ABackground::StaticClass(), SpawnParameters);
		FVector2D Dimensions = PongCamera->GetViewDimensions();
		Background->SetDimensions(Dimensions);

		World->SpawnActor(APongBall::StaticClass());

		FVector Scale = Background->GetScale();
		APongBounds* Bounds = World->SpawnActor<APongBounds>( APongBounds::StaticClass(), SpawnParameters);
		Bounds->SetScale( Scale );
	}
	Super::StartMatch();
}
