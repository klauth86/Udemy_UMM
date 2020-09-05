// Fill out your copyright notice in the Description page of Project Settings.


#include "UMM_GameInstance.h"
#include "UserWidget.h"

void UUMM_GameInstance::Host() {
	UE_LOG(LogTemp, Warning, TEXT("EXEC HOST"));
}

void UUMM_GameInstance::Join(const FString& address) {
	UE_LOG(LogTemp, Warning, TEXT("EXEC JOIN [%s]"), &address);
}

void UUMM_GameInstance::LoadMainMenu() {
	if (MainMenuUIClass) {

		MainMenuUI = CreateWidget<UUserWidget>(this, MainMenuUIClass);

	}
}