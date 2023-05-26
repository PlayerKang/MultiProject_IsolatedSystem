// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "ABAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


AABAIController::AABAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef
	(TEXT("/Script/AIModule.BlackboardData'/Game/WorkByKim/AI/BB_NPC.BB_NPC'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	} 

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef
	(TEXT("/Script/AIModule.BehaviorTree'/Game/WorkByKim/AI/NPC/BT_NPC.BT_NPC'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AABAIController::RunAI()
{
	UE_LOG(LogTemp, Warning, TEXT("RunAI Start"));
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		UE_LOG(LogTemp, Warning, TEXT("RunAI Start After UseBlackboard"));

		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AABAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	// nullptr != BTComponent
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
