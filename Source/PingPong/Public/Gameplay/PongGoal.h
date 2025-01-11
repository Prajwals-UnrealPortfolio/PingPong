// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongGoal.generated.h"

class UPaperSpriteComponent;

UCLASS()
class PINGPONG_API APongGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APongGoal(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetScale(FVector& Vector);

	void SetPosition(FVector& Position);

	float GetWidth();
	
private:

	UPaperSpriteComponent* Sprite;
};
