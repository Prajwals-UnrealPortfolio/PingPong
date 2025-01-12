// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PongPaddleAI.h"
#include "InputActionValue.h"
#include "PaperSpriteComponent.h"
#include "Gameplay/PongBall.h"

APongPaddleAI::APongPaddleAI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void APongPaddleAI::BeginPlay()
{
	Super::BeginPlay();
	Sprite->SetRelativeLocation( FVector( 200.0f, 10.f, 0.0f ) );
	Sprite->SetRelativeRotation( FRotator( 0.f, 0.f, 0.f ) );
}

void APongPaddleAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!PongBall)
	{
		return;
	}

	const float Deadzone = 2.0f;
	const float PositionDiff = GetActorLocation().Z - PongBall->GetActorLocation().Z;

	if(FMath::Abs(PositionDiff)<=Deadzone)
	{
		Move(FInputActionValue(0.f));
	}
	else if(PositionDiff > Deadzone)
	{
		Move(FInputActionValue(-1.f));
	}
	else
	{
		Move(FInputActionValue(1.f));
	}
	
}

void APongPaddleAI::SetBall(APongBall* Ball)
{
	this->PongBall = Ball;
}
