// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PongBall.h"

#include "AI/PongPaddleAI.h"
#include "Gameplay/PongPaddle.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Paper2D/Classes/PaperSprite.h"

APongBall::APongBall(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	const ConstructorHelpers::FObjectFinder<UPaperSprite> BallRef(TEXT("PaperSprite'/Game/Sprites/Ball.Ball'"));

	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComponent"));
	Sprite->SetSprite(BallRef.Object);
	RootComponent = Sprite;

	SetActorEnableCollision(true);
	Sprite->SetEnableGravity(false);
	Sprite->SetConstraintMode(EDOFMode::SixDOF);
	Sprite->GetBodyInstance()->bLockXRotation = true;
	Sprite->GetBodyInstance()->bLockYRotation = true;
	Sprite->GetBodyInstance()->bLockZRotation = true;
	Sprite->GetBodyInstance()->bLockXTranslation = false;
	Sprite->GetBodyInstance()->bLockYTranslation = true;
	Sprite->GetBodyInstance()->bLockZTranslation = false;

	Sprite->SetNotifyRigidBodyCollision(true);

	Sprite->SetRelativeLocation( FVector( 0.0f, 10.0f, 0.0f ) );
	Sprite->SetRelativeScale3D( FVector( 0.07f, 1.0f, 0.07f ) );

	Sprite->SetLinearDamping( 0.0f );
	Sprite->SetSimulatePhysics( true );

	Direction = FVector( 0.0f, 0.0f, 0.0f );
	Velocity = 0.0f;
}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();
	StartMove();
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float Time = (DeltaTime > 0.01f ? 0.0083f : DeltaTime);

	FTransform Transform = GetActorTransform();
	Transform.AddToTranslation(Direction * Velocity * Time);
	SetActorTransform(Transform);
}

void APongBall::StartMove()
{
	Direction = FVector( -1.0f, 0.0f, 0.0f );
	Velocity = 250.0f;
}

void APongBall::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Sprite->SetAllPhysicsAngularVelocityInDegrees(FVector( 0.0f, 0.0f, 0.0f ));
	Sprite->SetAllPhysicsLinearVelocity( FVector( 0.0f, 0.0f, 0.0f ) );

	Direction = Direction.MirrorByVector(HitNormal);
	
	if (Other->ActorHasTag("Paddle"))
	{
		APongPaddle* Paddle = Cast<APongPaddle>(Other);
		if(Paddle == nullptr)
		{
			return;
		}
		Direction.Z += (Paddle->GetZVelocity() / Velocity);
	}
}

