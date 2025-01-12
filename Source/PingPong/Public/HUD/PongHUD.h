// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PongHUD.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APongHUD : public AHUD
{
	GENERATED_BODY()

public:

	APongHUD(const FObjectInitializer& ObjectInitializer);

	virtual void DrawHUD() override;

	void DisplayScore();

	void DisplaySpaceText();

	void DisplayWaitingForSpace(bool bSpace);

	void SetScore(int PlayerScore, int AIScore);

private:

	int Score[2];

	bool bWaitingForSpace;
};
