// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PongGameState.h"
#include "Gameplay/PongPaddle.h"
#include "AI/PongPaddleAI.h"
#include "Gameplay/PongBall.h"
#include "Controllers/PongPlayerController.h"
#include "HUD/PongHUD.h"

APongGameState::APongGameState(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerScore = 0;
	AIScore = 0;
	CurrentState = PONG_STATES::WAITING_TO_START;
}

void APongGameState::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<APongPlayerController>(GetWorld()->GetFirstPlayerController());
	HUD = Cast<APongHUD>(Controller->GetHUD());
}

void APongGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsMatchInProgress())
	{
		switch (CurrentState)
		{
		case PONG_STATES::RESET:
			ResetBoard();
			PlayerPaddle->SetMoveAble(false);
			AIPaddle->SetMoveAble(false);
			CurrentState = PONG_STATES::WAITING_TO_START;
			break;
			case PONG_STATES::WAITING_TO_START:
				HUD->DisplayWaitingForSpace( true );
				if ( Controller->WasInputKeyJustReleased( EKeys::SpaceBar ) )
				{
					HUD->DisplayWaitingForSpace( false );
					PlayerPaddle->SetMoveAble(true);
					AIPaddle->SetMoveAble(true);
					CurrentState = PONG_STATES::PUSH_BALL;
				}
				break;
			case PONG_STATES::PUSH_BALL:
				PongBall->StartMove();
				CurrentState = PONG_STATES::PLAYING;
				break;
			case PONG_STATES::PLAYING:
				if (bPlayerScored || bAIScored)
				{
					HUD->SetScore( PlayerScore, AIScore );
					CurrentState = PONG_STATES::RESET;
				}
				break;
			default:
				CurrentState = PONG_STATES::RESET;
				break;
		}
	}
}

void APongGameState::SetBall(APongBall* Ball)
{
	this->PongBall = Ball;
	this->PongBall->OnActorBeginOverlap.AddDynamic(this, &APongGameState::BallOverlap);
}

void APongGameState::SetPaddles(APongPaddle* Player, APongPaddleAI* AI)
{
	PlayerPaddle = Player;
	AIPaddle = AI;
}

void APongGameState::BallOverlap(AActor* OverlappedActor,AActor* OtherActor)
{
	if(OtherActor->ActorHasTag("AIGoal"))
	{
		bPlayerScored = true;
        PlayerScore++;
	}
	if(OtherActor->ActorHasTag("PlayerGoal"))
    {
    	bAIScored = true;
        AIScore++;
    }
}

void APongGameState::ResetBoard()
{
	bPlayerScored = false;
	bAIScored = false;
	PongBall->ResetBall();
	PlayerPaddle->Reset();
	AIPaddle->Reset();
}
