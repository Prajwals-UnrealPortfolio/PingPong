// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "PongCamera.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APongCamera : public ACameraActor
{
	GENERATED_BODY()

public:

	APongCamera(const FObjectInitializer& ObjectInitializer);

	FVector2D GetViewDimensions();
};
