// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_Survivor.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APC_Survivor::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem)
	{
		SubSystem->AddMappingContext(InputContext, 0);
	}

}
