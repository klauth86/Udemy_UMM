// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MoveablePlatform.generated.h"

class FPrimitiveSceneProxy;
class UMoveByPointsComponent;

UCLASS()
class UMM_L03_API AMoveablePlatform : public AStaticMeshActor {

	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Moveable Platform")
	UMoveByPointsComponent* MoveByPointsComponent;

public:

	AMoveablePlatform();

	virtual void BeginPlay() override;
};
