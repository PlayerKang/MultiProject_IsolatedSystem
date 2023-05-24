// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_AttackInRange.h"
#include "AI/ABAI.h"
#include "AI/ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/ABCharacterAIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");

}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// ���� ������
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	// �����κ��� �������̽��� ���������� üũ��
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return false;
	}

	// TARGET ���� ������
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return false;
	}

	// ���� �� üũ�ؼ� TARGET ���� �������� �Ÿ��� ����
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	float AttackRangeWithRadius = AIPawn->GetAIDetectRange();

	// AI ���ݹ��� �ȿ� Ÿ�ٰŸ��� ������ True
	bResult = (DistanceToTarget <= AttackRangeWithRadius);
	return bResult;
}
