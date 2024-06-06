// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FFLogger.h"
#include "CameraControl_Component.generated.h"


//<summary>
//This class handles the camera controls (pitch and yaw), will also be in charge of Aiming
//</summary>
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYCROWD_V3_API UCameraControl_Component : public UActorComponent
{
	GENERATED_BODY()

private:	

	APawn* m_pawn;
	APlayerCameraManager* m_playerCamera;

	FFLogger m_debug;

	FVector2D m_accumulatedRotationInput{ 0.0f, 0.0f };

	//These variables are for aiming
	bool m_isAiming = false;
	bool m_isAnimating = false;
	bool m_isZoomingIn = true;

	float m_animationTimeElapsed = 0.0f;
	float m_zoomInAnimationDuration = 1.5f;
	float m_zoomOutAnimationDuration = 0.75f;

	float m_startFOV;
	float m_endFOV;


public:

	//These variables are for Rotation Interpolation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Controls")
	FVector2D lookSensitivity{ 1.5f, 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Controls")
	bool useSmoothRotation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Controls")
	float stoppingTolerance = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Controls")
	float cameraRotationSpeed = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Controls")
	bool invertYAxis = false;

	//These variables are for aiming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float fovReductionPercent = 30.0f;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	void ToggleSmoothRotation();

	void InitializeAim();

	void ZoomInAnimationTick();

	void ZoomOutAnimationTick();

	void StartAnimation();

	void StopAnimation();

	bool GetIsAiming();

public:
	// Sets default values for this component's properties
	UCameraControl_Component();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddRotationInput(FVector2D actionValue);

	UFUNCTION(BlueprintCallable)
	void StartAiming();

	UFUNCTION(BlueprintCallable)
	void StopAiming();


};
