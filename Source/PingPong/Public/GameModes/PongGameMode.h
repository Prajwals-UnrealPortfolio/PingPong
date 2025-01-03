// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PongGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APongGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	APongGameMode(const FObjectInitializer& ObjectInitializer);
	
	virtual void StartPlay() override;
};
