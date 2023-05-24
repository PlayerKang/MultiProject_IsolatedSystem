// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacterNonPlayer.h"

// Sets default values
AABCharacterNonPlayer::AABCharacterNonPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AABCharacterNonPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABCharacterNonPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AABCharacterNonPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AABCharacterNonPlayer::GetAIPatrolRadius()
{
	// 8미터
	return 800.0f;
}

float AABCharacterNonPlayer::GetAIDetectRange()
{
	// 4미터
	return 400.0f;
}

float AABCharacterNonPlayer::GetAIAttackRadius()
{
	// 폰과 폰사이의 거리 = 공격범위 + (공격반지름 * 2)
	//return Stat->GetTotalStat().AttackRange + Stat->GetAttackRadius() * 2;
	return 30.0f;
}

float AABCharacterNonPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void AABCharacterNonPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
}

void AABCharacterNonPlayer::AttackByAI()
{
}

