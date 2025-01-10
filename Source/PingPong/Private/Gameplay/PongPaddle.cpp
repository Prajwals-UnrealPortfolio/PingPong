// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PongPaddle.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Controllers/PongPlayerController.h"


APongPaddle::APongPaddle(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),
InputDirection(0.f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	const ConstructorHelpers::FObjectFinder<UPaperSprite> PaddleRef(TEXT("PaperSprite'/Game/Sprites/Paddle.Paddle'"));
	const ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMappingRef(TEXT("InputMappingContext'/Game/Input/IMC_Player.IMC_Player'"));
	const ConstructorHelpers::FObjectFinder<UInputAction> MovementActionRef(TEXT("InputAction'/Game/Input/InputActions/IA_Move.IA_Move'"));
	
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComponent"));
	Sprite->SetSprite(PaddleRef.Object);
	Sprite->GetBodyInstance()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	Sprite->GetBodyInstance()->SetObjectType( ECollisionChannel::ECC_Pawn );
	Sprite->GetBodyInstance()->SetResponseToChannel( ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap );
	DefaultMappingContext = DefaultMappingRef.Object;
	MoveAction = MovementActionRef.Object;

	MoveUp = true;
	MoveDown = true;
}

// Called when the game starts or when spawned
void APongPaddle::BeginPlay()
{
	Super::BeginPlay();
	Sprite->SetRelativeLocation( FVector( -200.0f, 10.f, 0.0f ) );
    Sprite->SetRelativeRotation( FRotator( 0.f, 0.f, 0.f ) );
    Sprite->SetRelativeScale3D( FVector( 0.1f, 1.0f, 0.1f ) );
    Sprite->SetAbsolute( true, true, true );

	if(Controller)
	{
		if(APongPlayerController* PongPlayerController = Cast<APongPlayerController>(Controller))
		{
			if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PongPlayerController->GetLocalPlayer()))
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(DefaultMappingContext,0);
			}
		}
	}
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
	
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APongPaddle::Move);
	}
}

void APongPaddle::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if ( OtherActor->ActorHasTag("Bounds"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
		if ( InputDirection > 0.0f )
		{
			MoveUp = false;
		}
		else if ( InputDirection < 0.0f )
		{
			MoveDown = false;
		}
	}
}

void APongPaddle::NotifyActorEndOverlap(AActor* OtherActor)
{
	if ( OtherActor->ActorHasTag("Bounds") )
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap Ends"));
		MoveUp = true;
		MoveDown = true;
	}
}

void APongPaddle::Move(const FInputActionValue& Value)
{
	FVector Direction = FVector( 0.0f, 0.0f, 75.0f );
	InputDirection = Value.Get<float>();
	InputDirection = FMath::Clamp(InputDirection, -1.f,1.f);
	if((MoveUp && InputDirection>0) || (MoveDown && InputDirection<0) )
	{
		FVector Location = GetActorLocation();
		Location += Direction * InputDirection * FApp::GetDeltaTime();
		Sprite->SetWorldLocation(Location);
	}
}

