// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/PongPaddle.h"
#include "PongPaddleAI.generated.h"

class APongBall;
/**
 * 
 */
UCLASS()
class PINGPONG_API APongPaddleAI : public APongPaddle
{
	GENERATED_BODY()

public:

	APongPaddleAI(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void SetBall(APongBall* Ball);

private:

	APongBall* PongBall;
	
};
