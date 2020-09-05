// Fill out your copyright notice in the Description page of Project Settings.


#include "UMM_GameInstance.h"
#include "Engine/Engine.h"
#include "UserWidget.h"

void UUMM_GameInstance::Host() {

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/ThirdPersonExampleMap");

	UE_LOG(LogTemp, Warning, TEXT("EXEC HOST"));
}

void UUMM_GameInstance::Join(const FString& address) {

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);

	UE_LOG(LogTemp, Warning, TEXT("EXEC JOIN [%s]"), &address);
}

void UUMM_GameInstance::LoadMainMenu() {
	if (MainMenuUIClass) {
		MainMenuUI = CreateWidget<UUserWidget>(this, MainMenuUIClass);
		MainMenuUI->AddToViewport();
	}
}