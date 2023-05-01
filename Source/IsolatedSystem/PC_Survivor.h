// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Survivor.generated.h"

/**
 * 
 */
UCLASS()
class ISOLATEDSYSTEM_API APC_Survivor : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		class UInputMappingContext* InputContext;

	virtual void BeginPlay() override;
	
};
