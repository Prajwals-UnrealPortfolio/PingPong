// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PongGameState.generated.h"

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
		WAITING_TO_START,
		PUSH_BALL,
		PLAYING,
		UPDATE_SCORE
	};

public:

	APongGameState(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;
	void SetBall( class APongBall* Ball );

private:

	PONG_STATES CurrentState;

	APongBall* PongBall;
};
