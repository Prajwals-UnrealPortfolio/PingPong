// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PongHUD.h"

APongHUD::APongHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Score[0] = 0;
	Score[1] = 0;
	bWaitingForSpace = false;
}

void APongHUD::DrawHUD()
{
	Super::DrawHUD();
	DisplayScore();
	if ( bWaitingForSpace )
	{
		DisplaySpaceText();
	}
}

void APongHUD::DisplayScore()
{
	FVector2D SLoc;
	GetOwningPlayerController( )->ProjectWorldLocationToScreen( FVector( -160.f, 0.0f, 150.0f ), SLoc );
	FString s = "Score: " + FString::FromInt( Score[0] ) + " - " + FString::FromInt( Score[1] );
	DrawText( s, FLinearColor::Black, SLoc.X, SLoc.Y );
}

void APongHUD::DisplaySpaceText()
{
	FVector2D SLoc;
	GetOwningPlayerController()->ProjectWorldLocationToScreen( FVector( -180.f, 0.0f, -150.f ), SLoc );
	FString s = "Press Space to Begin.";
	DrawText( s, FLinearColor::Black, SLoc.X, SLoc.Y, GEngine->GetMediumFont());
}

void APongHUD::DisplayWaitingForSpace(bool bSpace)
{
	bWaitingForSpace = bSpace;
}

void APongHUD::SetScore(int PlayerScore, int AIScore)
{
	Score[0] = PlayerScore;
	Score[1] = AIScore;
}
