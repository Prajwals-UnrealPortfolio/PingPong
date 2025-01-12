// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PongGameState.generated.h"

class APongPaddleAI;
class APongPaddle;
class APongHUD;
class APongPlayerController;
class APongBall;
/**
 * 
 */
UCLASS()
class PINGPONG_API APongGameState : public AGameState
{
	GENERATED_BODY()

	enum PONG_STATES
	{
		RESET,
		WAITING_TO_START,
		PUSH_BALL,
		PLAYING
	};

public:

	APongGameState(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	void SetBall( APongBall* Ball );
	void SetPaddles(APongPaddle* Player, APongPaddleAI* AI);

	UFUNCTION()
	void BallOverlap(AActor* OverlappedActor,AActor* OtherActor);

private:

	void ResetBoard();

private:

	PONG_STATES CurrentState;

	APongBall* PongBall;

	bool bAIScored;
	bool bPlayerScored;

	int AIScore;
	int PlayerScore;

	APongPaddle* PlayerPaddle;
	APongPaddleAI* AIPaddle;

	APongPlayerController* Controller;
	APongHUD* HUD;
};
