#include "InteractAction_Component.h"
#include "FFLogger.h"
#include "CartInteractionSubsystem.h"


UInteractAction_Component::UInteractAction_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UInteractAction_Component::BeginPlay()
{
	Super::BeginPlay();

	m_CartInteractionSubsystem = GetWorld()->GetSubsystem<UCartInteractionSubsystem>();
	m_Owner = GetOwner();
}

void UInteractAction_Component::TryToInteract()
{
	m_CartInteractionSubsystem->RequestInteractionWithCart(m_Owner);
}

