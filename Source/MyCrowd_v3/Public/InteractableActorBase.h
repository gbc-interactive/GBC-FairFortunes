// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActorBase.generated.h"

UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Interactable Actor"))
class MYCROWD_V3_API AInteractableActorBase : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void ReceiveInteract(AActor* Interactor);
};
