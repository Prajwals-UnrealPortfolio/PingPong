// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PongGameState.h"
#include "Gameplay/PongBall.h"

APongGameState::APongGameState(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentState = PONG_STATES::WAITING_TO_START;
}

void APongGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsMatchInProgress())
	{
		switch (CurrentState)
		{
			case PONG_STATES::WAITING_TO_START:
				CurrentState = PONG_STATES::PUSH_BALL;
				break;
			case PONG_STATES::PUSH_BALL:
				PongBall->StartMove();
				CurrentState = PONG_STATES::PLAYING;
				break;
			case PONG_STATES::PLAYING:
				break;
			case PONG_STATES::UPDATE_SCORE:
				CurrentState = PONG_STATES::WAITING_TO_START;
				break;
			default:
				CurrentState = PONG_STATES::WAITING_TO_START;
				break;
		}
	}
}

void APongGameState::SetBall(APongBall* Ball)
{
	this->PongBall = Ball;
}
