// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "AI/ABAI.h"
#include "AIController.h"
#include "Interface/ABCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Physics/ABCollision.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	// ��� �̸��� ��������
	NodeName = TEXT("Detect");
	// 1�� ������ �����ϵ��� ���� ����
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// AI�� �����ϰ� �ִ� ���� ���� ��������, 
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	// �� ���������� �׳� ����..
	if (nullptr == ControllingPawn)
	{
		return;
	}

	// ���� ��ġ, ���� ���� ���� �� �����´�
	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();

	// ���� �� �� ������ �� ����ó��
	if (nullptr == World)
	{
		return;
	}

	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	// AI�������̽����� ������ ������ ������
	float DetectRadius = AIPawn->GetAIDetectRange();


	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);

	// �÷��̾ �ټ��̴ϱ� ��������Ƽ ��
	// �׷��� ������ TArray�� �迭 �� ��!
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		CCHANNEL_ABACTION,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	// ������ �ȴٸ�
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());

			// ���� �����ϴ°� �÷��̾� ��Ʈ�ѷ��� ��� 
			// ��, �÷��̾� �����ϴ� ����� �׷��ִ� ����
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				// �����忡 Ÿ�ٰ�(�÷��̾�) ����
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(),
					FColor::Green, false, 0.27f);

				return;
			}
		}
	}

	// ���� ���������� �÷��̾ �� ã�� �� �ΰ� ����, ���������� ǥ��
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
