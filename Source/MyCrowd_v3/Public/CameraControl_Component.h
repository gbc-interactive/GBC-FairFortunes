// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraControl_Component.generated.h"


//<summary>
//This class handles the camera controls (pitch and yaw), will also be in charge of Aiming
//</summary>
UCLASS( ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class MYCROWD_V3_API UCameraControl_Component : public UActorComponent
{
	GENERATED_BODY()

private:	

	APawn* m_pawn;
	APlayerCameraManager* m_playerCamera;

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
	FVector2D m_lookSensitivity{ 1.5f, 1.0f };

	FVector2D m_ADSLookSensitivity{ 1.5f, 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Controls")
	bool m_useSmoothRotation = true;

	float m_stoppingTolerance = 0.1f;

	float m_cameraRotationSpeed = 1.5f;

	bool m_invertYAxis = false;

	float m_fovReductionPercent = 30.0f;

	DECLARE_DELEGATE(ADSChangedDelegate);

	ADSChangedDelegate ADSBeginEvent;
	ADSChangedDelegate ADSEndEvent;

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

	UFUNCTION(BlueprintCallable)
	inline bool GetIsAiming() { return m_isAiming; }
};
