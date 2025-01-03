// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PongPaddle.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

APongPaddle::APongPaddle(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	const ConstructorHelpers::FObjectFinder<UPaperSprite> BallRef(TEXT("PaperSprite'/Game/Sprites/Paddle.Paddle'"));

	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComponent"));
	Sprite->SetSprite(BallRef.Object);
}

// Called when the game starts or when spawned
void APongPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APongPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APongPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

