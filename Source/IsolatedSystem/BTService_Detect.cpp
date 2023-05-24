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
	// 노드 이름을 지정해줌
	NodeName = TEXT("Detect");
	// 1초 단위로 수행하도록 단위 설정
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// AI로 제어하고 있는 폰의 정보 가져오고, 
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	// 폰 못가져오면 그냥 리턴..
	if (nullptr == ControllingPawn)
	{
		return;
	}

	// 폰의 위치, 폰이 속한 월드 값 가져온다
	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();

	// 월드 값 못 가져올 때 예외처리
	if (nullptr == World)
	{

		return;
	}

	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	// AI인터페이스에서 감지할 영역을 가져옴
	float DetectRadius = AIPawn->GetAIDetectRange();


	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);

	// 플레이어가 다수이니까 오버랩멀티 씀
	// 그래서 위에서 TArray로 배열 쓴 것!
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		CCHANNEL_ABACTION,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	// 감지가 된다면
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());

			// 폰을 조정하는게 플레이어 컨트롤러인 경우 
			// 즉, 플레이어 감지하는 디버그 그려주는 내용
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				// 블랙보드에 타겟값(플레이어) 저장
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(),
					FColor::Green, false, 0.27f);

				return;
			}
		}
	}

	// 폰은 감지했지만 플레이어를 못 찾을 때 널값 설정, 붉은색으로 표시
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
