// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "MoveByPointsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMM_L03_API UMoveByPointsComponent : public UPrimitiveComponent {

	GENERATED_BODY()

public:	
	UMoveByPointsComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void StartMovement(int32 currentTarget);

#if !UE_BUILD_SHIPPING
	//~ Begin UPrimitiveComponent Interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override { return nullptr; }
	//~ End UPrimitiveComponent Interface.
#endif

protected:

	UPROPERTY(EditAnywhere, Category = "AMoveablePlatform")
		bool ThereAndBackAgain;

	UPROPERTY(EditAnywhere, Category = "AMoveablePlatform")
		TMap<FVector, float> Points;

	float TimeLeft;

	int32 CurrentTarget = INDEX_NONE;
};
