// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractAction_Component.generated.h"


UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class MYCROWD_V3_API UInteractAction_Component : public UActorComponent
{
	GENERATED_BODY()




private:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;
	
	UWorld* m_world;


public:	
	// Sets default values for this component's properties
	UInteractAction_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TryToInteract();

};
