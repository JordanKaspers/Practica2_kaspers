// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
  // Get Patrol Route
  AAIController* AIController = OwnerComp.GetAIOwner();
  APawn* ControlledPawn = AIController->GetPawn();
  UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

  if (!ensure(PatrolRoute))
  {
    return EBTNodeResult::Failed;
  }

  TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();
  if (PatrolPoints.Num() == 0)
  {
    UE_LOG(LogTemp, Warning, TEXT("Missing patrol points!"));
    return EBTNodeResult::Failed;
  }

  // Next waypoint
  UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
  int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
  BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);

  // Cycle index
  int32 NextIndex = (Index + 1) % PatrolPoints.Num();
  BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);


  return EBTNodeResult::Succeeded;
}

