// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControls/CameraControl_Component.h"

#include "Evaluation/Blending/MovieSceneBlendType.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCameraControl_Component::UCameraControl_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraControl_Component::BeginPlay()
{
	Super::BeginPlay();

	m_pawn = Cast<APawn>(GetOwner());

	if(UWorld * World = GetWorld())
	{
		m_playerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	InitializeAim();

}


// Called every frame
void UCameraControl_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//RotationInterpolation

	if(useSmoothRotation == true)
	{
		if(m_accumulatedRotationInput.Length() > stoppingTolerance)
		{
			//creating variables for Yaw Input
			float cameraSpeed = DeltaTime * cameraRotationSpeed;
			float cameraRotationInputX = m_accumulatedRotationInput.X * cameraSpeed;
			float cameraRotationInputY = m_accumulatedRotationInput.Y * cameraSpeed;

			//adding to Yaw
			m_pawn->AddControllerYawInput(cameraRotationInputX);

			//setting accumulatedRotationInput
			m_accumulatedRotationInput.X = m_accumulatedRotationInput.X - cameraRotationInputX;

			//Setting Pitch Input
			if(invertYAxis == true)
			{
				//adding to Pitch
				m_pawn->AddControllerPitchInput(cameraRotationInputY * -1.0f);
				//setting accumulatedRotationInput
				m_accumulatedRotationInput.Y = m_accumulatedRotationInput.Y - (cameraRotationInputY * -1.0f);
			}
			else
			{
				//adding to Pitch
				m_pawn->AddControllerPitchInput(cameraRotationInputY);
				//setting accumulatedRotationInput
				m_accumulatedRotationInput.Y = m_accumulatedRotationInput.Y - cameraRotationInputY;
			}

		}
	}


	//isAiming
	if (m_isAnimating == true)
	{
		if (m_isZoomingIn == true)
		{
			ZoomInAnimationTick();
		}
		else
		{
			ZoomOutAnimationTick();
		}

		m_animationTimeElapsed = m_animationTimeElapsed + DeltaTime;
	}



}

void UCameraControl_Component::AddRotationInput(FVector2D actionValue)
{

	//Setting input vector
	FVector2D inputVector = lookSensitivity * actionValue;

	if(useSmoothRotation == true)
	{
		m_accumulatedRotationInput.X = inputVector.X + m_accumulatedRotationInput.X;
		m_accumulatedRotationInput.Y = inputVector.Y + m_accumulatedRotationInput.Y;
	}
	else
	{
		m_pawn->AddControllerYawInput(inputVector.X);

		if(invertYAxis == true)
		{
			m_pawn->AddControllerPitchInput(inputVector.Y * -1.0f);
		}
		else
		{
			m_pawn->AddControllerPitchInput(inputVector.Y);
		}

	}

}

void UCameraControl_Component::ToggleSmoothRotation()
{
	useSmoothRotation = !useSmoothRotation;
	m_accumulatedRotationInput = FVector2D{0.0f, 0.0f};
}

void UCameraControl_Component::StartAiming()
{
	//if player is aiming
	m_isAiming = true;
	
	if (m_isAnimating == true)
	{
		StopAnimation();
	}

	StartAnimation();
	ToggleSmoothRotation();
	m_pawn->bUseControllerRotationYaw = true;

}

void UCameraControl_Component::StopAiming()
{
	m_isAiming = false;

	if (m_isAnimating == true)
	{
		StopAnimation();
	}

	StartAnimation();
	ToggleSmoothRotation();
	m_pawn->bUseControllerRotationYaw = false;
}

void UCameraControl_Component::InitializeAim()
{
	//getting FOV angle from camera
	m_startFOV = m_playerCamera->GetFOVAngle();
	//variables for getting endFOV
	float reducedFOV = fovReductionPercent / 100.0f;
	float middleFOV = m_startFOV * reducedFOV;
	//setting endFOV using the startFOV - middleFOV
	m_endFOV = m_startFOV - middleFOV;
}

void UCameraControl_Component::ZoomInAnimationTick()
{
	//uses zoom in
	float animationTime = m_animationTimeElapsed / m_zoomInAnimationDuration;
	float fov = m_playerCamera->GetFOVAngle(); // could make startFOV

	if(animationTime <= 1.0f)
	{
		//uses endFOV because we are zooming in
		m_playerCamera->SetFOV(FMath::Lerp(fov, m_endFOV, animationTime));
	}
	else
	{
		StopAnimation();
	}


}

void UCameraControl_Component::ZoomOutAnimationTick()
{
	//uses zoom out instead of in
	float animationTime = m_animationTimeElapsed / m_zoomOutAnimationDuration;
	float fov = m_playerCamera->GetFOVAngle(); // could make startFOV

	if (animationTime <= 1.0f)
	{
		//uses StartFov because we are going back to original camera
		m_playerCamera->SetFOV(FMath::Lerp(fov, m_startFOV, animationTime));
	}
	else
	{
		StopAnimation();
	}
}

void UCameraControl_Component::StartAnimation()
{
	m_isAnimating = true;
}

void UCameraControl_Component::StopAnimation()
{
	m_isAnimating = false;
	m_animationTimeElapsed = 0.0f;
	m_isZoomingIn = !m_isZoomingIn;
}

bool UCameraControl_Component::GetIsAiming()
{
	return m_isAiming;
}