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

	Sprite->GetBodyInstance()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sprite->GetBodyInstance()->SetObjectType(ECollisionChannel::ECC_WorldStatic);

	Sprite->SetVisibility(false);
	
	Tags.Add(FName("Bounds"));
}

// Called when the game starts or when spawned
void APongBounds::BeginPlay()
{
	Super::BeginPlay();

	Sprite->SetRelativeLocation( FVector( 0.0f, 10.f, -10.0f ) );
	Sprite->SetAbsolute( true, true, true );
}

// Called every frame
void APongBounds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APongBounds::SetScale(FVector& Vector)
{
	Vector.X = FMath::Max(Vector.X, 0.01f);
	Vector.Y = FMath::Max(Vector.Y, 0.01f);
	Vector.Z = FMath::Max(Vector.Z, 0.01f);
	Sprite->SetRelativeScale3D(Vector);
}

