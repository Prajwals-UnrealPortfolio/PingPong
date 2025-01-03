// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Background.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Paper2D/Classes/PaperSprite.h"

ABackground::ABackground(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	const ConstructorHelpers::FObjectFinder<UPaperSprite> BackgroundSpriteRef( TEXT( "PaperSprite'/Game/Sprites/Background.Background'" ) );

	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComponent"));
	Sprite->SetSprite(BackgroundSpriteRef.Object);
	
}

void ABackground::SetWidth(float Width) const
{
	const float sourceWidth = Sprite->GetSprite()->GetSourceSize().X;
	const float scale = Width/sourceWidth;
	FVector ScaleV = Sprite->GetRelativeScale3D();
	ScaleV.X = scale;
	Sprite->SetRelativeScale3D(ScaleV);
}

void ABackground::SetHeight(float Height) const 
{
	const float sourceHeight = Sprite->GetSprite()->GetSourceSize().Y;
	const float scale = Height/sourceHeight;
	FVector ScaleV = Sprite->GetRelativeScale3D();
	ScaleV.Z = scale;
	Sprite->SetRelativeScale3D(ScaleV);
}

void ABackground::SetDimensions(const FVector2D& Dimensions) const
{
	SetWidth(Dimensions.X);
	SetHeight(Dimensions.Y);
}


