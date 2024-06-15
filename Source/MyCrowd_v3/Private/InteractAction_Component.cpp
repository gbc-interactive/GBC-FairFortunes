// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractAction_Component.h"
#include "FFLogger.h"
#include <InteractableActor.h>

// Sets default values for this component's properties
UInteractAction_Component::UInteractAction_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractAction_Component::BeginPlay()
{
	Super::BeginPlay();

	m_world = GetWorld();
	
}


// Called every frame
void UInteractAction_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractAction_Component::TryToInteract()
{
	//FFLogger::LogMessage(LogMessageSeverity::Debug, "Checking for interactable items");
	
	
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;
	FVector TraceStart = GetOwner()->GetActorLocation();
	FVector TraceEnd = TraceStart + GetOwner()->GetActorForwardVector() * 1000.0f;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams))
	{
		// If the trace hit something, bBlockingHit will be true,
		// and its fields will be filled with detailed info about what was hit
		if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
		{
			//FFLogger::LogMessage(LogMessageSeverity::Debug, "Actor hit: " + Hit.GetActor()->GetName());
			AInteractableActor* interactableActor = Cast<AInteractableActor>(Hit.GetActor());
			if (IsValid(interactableActor))
			{
				//FFLogger::LogMessage(LogMessageSeverity::Debug, "Interactable Actor found: " + interactableActor->GetName());
				interactableActor->ReceiveInteract(GetOwner());
			}
		}
		else
		{
			//FFLogger::LogMessage(LogMessageSeverity::Debug, "No Actors were hit");
		}
	}
	else
	{
		//FFLogger::LogMessage(LogMessageSeverity::Debug, "No Actors were hit");
	
	}

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	//FFLogger::LogMessage(LogMessageSeverity::Debug, "Tracing line: " + TraceStart.ToString() + " to " + TraceEnd.ToString());

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		//FFLogger::LogMessage(LogMessageSeverity::Debug, "Actor hit: " + Hit.GetActor()->GetName());
	}
	else 
	{
		//FFLogger::LogMessage(LogMessageSeverity::Debug, "No Actors were hit");
	}
}

