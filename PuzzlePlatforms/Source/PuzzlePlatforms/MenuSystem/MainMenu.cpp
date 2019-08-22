// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize() {

	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(Host != nullptr)) { return false; }

	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface) {
	this->MenuInterface = MenuInterface;
}

void UMainMenu::Setup() {
	
	this->bIsFocusable = true;
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) { return; }

	FInputModeUIOnly FInputModeData;
	FInputModeData.SetWidgetToFocus(this->TakeWidget());
	FInputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(FInputModeData);

	PlayerController->bShowMouseCursor = true;

}

void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) {
	
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) { return; }

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;

}

void UMainMenu::HostServer() {
	
	if (MenuInterface != nullptr) {
		MenuInterface->Host();
	}
}
