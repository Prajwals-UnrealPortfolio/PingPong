// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Background.generated.h"

class UPaperSpriteComponent;

UCLASS()
class PINGPONG_API ABackground : public AActor
{
	GENERATED_BODY()
	
public:
	
	ABackground(const FObjectInitializer& ObjectInitializer);
	
	void SetDimensions(const FVector2D& Dimensions) const;

	FVector GetScale() const;

private:

	void SetWidth(float Width) const;
	void SetHeight(float Height) const;
	
	UPaperSpriteComponent* Sprite;
};
