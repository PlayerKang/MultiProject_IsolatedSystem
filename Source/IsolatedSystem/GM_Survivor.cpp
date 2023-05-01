// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Survivor.h"

#include "PC_Survivor.h"
#include "Character_Survivor.h"

AGM_Survivor::AGM_Survivor()
{
	PlayerControllerClass = APC_Survivor::StaticClass();
	DefaultPawnClass = ACharacter_Survivor::StaticClass();
}
