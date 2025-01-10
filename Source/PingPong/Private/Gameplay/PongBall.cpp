// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PongBall.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Paper2D/Classes/PaperSprite.h"

APongBall::APongBall(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	const ConstructorHelpers::FObjectFinder<UPaperSprite> BallRef(TEXT("PaperSprite'/Game/Sprites/Ball.Ball'"));

	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComponent"));
	Sprite->SetSprite(BallRef.Object);
}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();

	Sprite->SetRelativeLocation( FVector( 0.0f, 10.0f, 0.0f ) );
	Sprite->SetRelativeScale3D( FVector( 0.07f, 1.0f, 0.07f ) );
	Sprite->SetAbsolute( true, true, true );
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

