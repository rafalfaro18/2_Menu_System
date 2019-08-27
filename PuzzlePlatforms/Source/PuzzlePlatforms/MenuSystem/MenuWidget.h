// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Setup();

	virtual void OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) override;

	void SetMenuInterface(IMenuInterface* MenuInterface);

protected:

	IMenuInterface* MenuInterface;

};
