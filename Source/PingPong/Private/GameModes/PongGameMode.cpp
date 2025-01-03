// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PongGameMode.h"

#include "Gameplay/PongPaddle.h"

APongGameMode::APongGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultPawnClass = APongPaddle::StaticClass();
}

void APongGameMode::StartPlay()
{
	Super::StartPlay();
	Super::StartMatch();
}
