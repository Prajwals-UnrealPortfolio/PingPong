// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PongGameMode.h"

#include "AI/PongPaddleAI.h"
#include "Camera/PongCamera.h"
#include "Controllers/PongPlayerController.h"
#include "Gameplay/Background.h"
#include "Gameplay/PongBall.h"
#include "Gameplay/PongBounds.h"
#include "Gameplay/PongGoal.h"
#include "Gameplay/PongPaddle.h"
#include "GameState/PongGameState.h"

APongGameMode::APongGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = APongPlayerController::StaticClass();
	DefaultPawnClass = APongPaddle::StaticClass();
	GameStateClass = APongGameState::StaticClass();
}

void APongGameMode::StartPlay()
{
	Super::StartPlay();
	UWorld* const World = GetWorld();
	if (!ensure(World))
	{
		return;
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//Camera
	APongCamera* PongCamera = World->SpawnActor<APongCamera>(APongCamera::StaticClass(),SpawnParameters);
	if(!ensure(PongCamera))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn PongCamera"));
		return;
	}
	
	//Player Controller
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController))
	{
	    UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController"));
	    return;
	}
	PlayerController->SetViewTarget(PongCamera);
	
	//Background
	ABackground* Background = World->SpawnActor<ABackground>(ABackground::StaticClass(), SpawnParameters);
	FVector2D Dimensions = PongCamera->GetViewDimensions();
	Background->SetDimensions(Dimensions);
	FVector Scale = Background->GetScale();
	
	//Bounds
	APongBounds* Bounds = World->SpawnActor<APongBounds>( APongBounds::StaticClass(), SpawnParameters);
	Bounds->SetScale( Scale );
	
	//PongBall
	APongBall* PongBall = World->SpawnActor<APongBall>(APongBall::StaticClass());
	if (!ensure(PongBall))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn PongBall"));
		return;
	}
	//GameState
	APongGameState* PongGameState = GetGameState<APongGameState>();
	if (!ensure(PongGameState))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get PongGameState"));
		return;
	}

	//Goals
	APongGoal* PlayerGoal = World->SpawnActor<APongGoal>( APongGoal::StaticClass(),SpawnParameters);
	APongGoal* AIGoal = World->SpawnActor<APongGoal>( APongGoal::StaticClass(),SpawnParameters);

	PlayerGoal->SetScale(Scale);
	AIGoal->SetScale(Scale);

	PlayerGoal->Tags.Add(FName("PlayerGoal"));
	AIGoal->Tags.Add(FName("AIGoal"));

	//Paddles
	APongPaddle* PlayerPaddle = Cast<APongPaddle>(World->GetFirstPlayerController()->GetPawn());
	APongPaddleAI* AIPaddle = World->SpawnActor<APongPaddleAI>(APongPaddleAI::StaticClass(), SpawnParameters);
	PlayerPaddle->Tags.Add(FName("PlayerPaddle"));
	AIPaddle->Tags.Add(FName("AIPaddle"));

	FVector PlayerPos, AIPos;
	PlayerPos.Y = 10.f;
	AIPos.Y = 10.f;
	PlayerPos.X = PlayerPaddle->GetPosition().X - ( PlayerGoal->GetWidth() * Scale.X ) / 2;
	AIPos.X = 5.0f + AIPaddle->GetPosition().X + ( PlayerGoal->GetWidth() * Scale.X ) / 2;
	PlayerPos.Z = 0.f;
	AIPos.Z = 0.f;

	PlayerGoal->SetPosition( PlayerPos );
	AIGoal->SetPosition( AIPos );

	AIPaddle->SetBall(PongBall);
	PongGameState->SetBall(PongBall);
	
	Super::StartMatch();
}
