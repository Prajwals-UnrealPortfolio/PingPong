// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PongBounds.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"


APongBounds::APongBounds(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	const ConstructorHelpers::FObjectFinder<UPaperSprite> BoundsRef(TEXT("PaperSprite'/Game/Sprites/Bounds.Bounds'"));

	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComponent"));
	Sprite->SetSprite(BoundsRef.Object);
}

// Called when the game starts or when spawned
void APongBounds::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APongBounds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

