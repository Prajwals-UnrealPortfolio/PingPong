// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongPaddle.generated.h"

class UInputAction;
struct FInputActionValue;
class UInputMappingContext;
class UPaperSpriteComponent;

UCLASS()
class PINGPONG_API APongPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APongPaddle(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	float GetZVelocity();
	
	FVector GetPosition();

protected:

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Paddle)
	UPaperSpriteComponent* Sprite;
	
	void Move(const FInputActionValue& Value);
	
private:
	UPROPERTY(VisibleAnywhere)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere)
	UInputAction* MoveAction;
	
	bool MoveUp;
	bool MoveDown;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float InputDirection;

	float Velocity;
};
