// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractAction_Component.generated.h"

class UCartInteractionSubsystem;

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class MYCROWD_V3_API UInteractAction_Component : public UActorComponent
{
	GENERATED_BODY()

private:

	
	UCartInteractionSubsystem* m_CartInteractionSubsystem;
	AActor* m_Owner;
public:	
	// ctor
	UInteractAction_Component();

protected:
	// onStart
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TryToInteract();

};
