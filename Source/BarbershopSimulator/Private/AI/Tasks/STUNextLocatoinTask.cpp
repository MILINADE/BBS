// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/STUNextLocatoinTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/Controller.h"
#include "AIController.h"

USTUNextLocatoinTask::USTUNextLocatoinTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type USTUNextLocatoinTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSys) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();
	if (!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if (!CenterActor) return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}

	const auto Found = NavSys->GetRandomPointInNavigableRadius(Location, Radius, NavLocation);
	if(!Found) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
