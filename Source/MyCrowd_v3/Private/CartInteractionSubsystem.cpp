#include "CartInteractionSubsystem.h"
#include "InteractableActorBase.h"
#include "FFLogger.h"
#include "PlayerStatsManagementSubsystem.h"


void UCartInteractionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UPlayerStatsManagementSubsystem* dataManager = (UPlayerStatsManagementSubsystem*) Collection.InitializeDependency(UPlayerStatsManagementSubsystem::StaticClass());
	
	if (!dataManager)
	{
		return;
	}

	dataManager->DataLoadCompleteEvent.AddUObject(this, &UCartInteractionSubsystem::OnPlayerDataLoaded);
}

void UCartInteractionSubsystem::OnPlayerDataLoaded(const UPlayerStatsManagementSubsystem* dataManager)
{
	const FPlayerInteractionStats* interactStats = dataManager->GetInteractionStats();
	m_InteractionRaycastChannel = interactStats->interactionRaycastChannel;
	m_playerInteractionRange = interactStats->interactionRange;
}

void UCartInteractionSubsystem::RequestInteractionWithCart(AActor* interactor)
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;
	FVector TraceStart = interactor->GetActorLocation();
	FVector TraceEnd = TraceStart + (interactor->GetActorForwardVector() * m_playerInteractionRange);

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(interactor);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, m_InteractionRaycastChannel, QueryParams))
	{
		// If the trace hit something, bBlockingHit will be true,
		// and its fields will be filled with detailed info about what was hit
		if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
		{
			FFLogger::LogMessage(LogMessageSeverity::Debug, "Actor hit: " + Hit.GetActor()->GetName());
			AInteractableActorBase* interactableActor = Cast<AInteractableActorBase>(Hit.GetActor());
			if (IsValid(interactableActor))
			{
				FFLogger::LogMessage(LogMessageSeverity::Debug, "Interactable Actor found: " + interactableActor->GetName());
				interactableActor->ReceiveInteract(interactor);
			}
		}
		else
		{
			FFLogger::LogMessage(LogMessageSeverity::Debug, "No Actors were hit");
		}
	}
	else
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "No Actors were hit");
	}

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Tracing line: " + TraceStart.ToString() + " to " + TraceEnd.ToString());

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "Actor hit: " + Hit.GetActor()->GetName());
	}
	else
	{
		FFLogger::LogMessage(LogMessageSeverity::Debug, "No Actors were hit");
	}
}
