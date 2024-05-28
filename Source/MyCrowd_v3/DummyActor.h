// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DummyActor.generated.h"


/// <summary>
/// Class exists just to trigger the conversion of the project from blueprint-only to C++. Do not use this class for anything, it will be deleted in the future.
/// </summary>

UCLASS()
class MYCROWD_V3_API ADummyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyActor();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

};
