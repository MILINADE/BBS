// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/STUAIPerceptionComponent.h"
#include "AI/STUAIController.h"
#include "STUUtils.h"
#include "Component/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosesEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if(PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PercieveActor);
		if (HealthComponent && !HealthComponent->IsDead()) //TODO check if enemies or not
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}

		}
	}

	return BestPawn;
}
