// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PongGoal.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

APongGoal::APongGoal(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	const ConstructorHelpers::FObjectFinder<UPaperSprite> GoalRef(TEXT("PaperSprite'/Game/Sprites/Goal.Goal'"));

	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComponent"));
	Sprite->SetSprite(GoalRef.Object);
	RootComponent = Sprite;

	Sprite->GetBodyInstance()->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
	Sprite->GetBodyInstance()->SetObjectType( ECollisionChannel::ECC_WorldStatic );
	Sprite->GetBodyInstance()->SetResponseToAllChannels( ECollisionResponse::ECR_Overlap );
	Sprite->SetVisibility( true );
}

// Called when the game starts or when spawned
void APongGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APongGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APongGoal::SetScale(FVector& Vector)
{
	SetActorRelativeScale3D(Vector);
}

void APongGoal::SetPosition(FVector& Position)
{
	SetActorRelativeLocation(Position);
}

float APongGoal::GetSourceWidth()
{
	return Sprite->GetSprite()->GetSourceSize().X;
}

