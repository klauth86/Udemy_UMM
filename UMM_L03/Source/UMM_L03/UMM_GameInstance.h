// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UMM_GameInstance.generated.h"

class UUserWidget;

UCLASS()
class UMM_L03_API UUMM_GameInstance : public UGameInstance {

	GENERATED_BODY()
	
public:

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& address);

	UFUNCTION(BlueprintCallable, Category = "UMM Game Instance")
		void LoadMainMenu();

protected:

	TSubclassOf<UUserWidget> MainMenuUIClass;

	UUserWidget* MainMenuUI;

};
