// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/PongCamera.h"
#include "Camera/CameraComponent.h"

APongCamera::APongCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UCameraComponent* PongCameraComponent = GetCameraComponent();
	PongCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	PongCameraComponent->SetRelativeLocation(FVector(0.f,100.f,0.f));
	PongCameraComponent->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
	PongCameraComponent->SetAbsolute(true, true, true);
}

FVector2D APongCamera::GetViewDimensions()
{
	UCameraComponent* PongCameraComponent = GetCameraComponent();
	FVector2D Dimensions;
	Dimensions.X = PongCameraComponent->OrthoWidth;
	Dimensions.Y = 1/ (PongCameraComponent->AspectRatio / PongCameraComponent->OrthoWidth);
	UE_LOG(LogTemp, Warning, TEXT("Ortho Width : %f"),Dimensions.X);
	UE_LOG(LogTemp, Warning, TEXT("Aspect Ratio : %f"),PongCameraComponent->AspectRatio);
	return Dimensions;
}
