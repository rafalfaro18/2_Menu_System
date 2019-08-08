// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	
	if (!ensure(MenuBPClass.Class != nullptr)) {
		return;
	}

	MenuClass = MenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init() {
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::Host() {
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) { return; }

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString & Address) {
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) { return; }

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) { return; }

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
