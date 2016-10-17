// Fill out your copyright notice in the Description page of Project Settings.

#include "Park.h"
#include "MyGameInstance.h"
#include "MySaveGame.h"
#include "Blueprint/UserWidget.h"


void UMyGameInstance::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void UMyGameInstance::CheckActivationState()
{
	UMySaveGame* SaveGameObject = LoadSaveGameObject();

	// In case application already activated
	if (SaveGameObject->bActivated)
	{
		ShowMainMenu();
		return;
	}

	// In case the app is not activated
	FDateTime CurDateTime = FDateTime::Now();
	// Check to see if system time is not fabricated
	if (SaveGameObject->LastDateTime < CurDateTime)
	{
		// Time is acceptable
		SaveGameObject->LastDateTime = CurDateTime;
		SaveSaveGameObject(SaveGameObject);
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, SaveGameObject->ExpirationDate.ToString());

		if (SaveGameObject->ExpirationDate > CurDateTime)
		{
			ShowMainMenu();
			return;
		}
		else
		{
			ShowEpirationError();
			return;
		}
	}
	else
	{
		// Time is not acceptable
		ShowSystemTimeError();
		return;
	}
}

void UMyGameInstance::Activate()
{
	UMySaveGame* SaveGameObject = LoadSaveGameObject();
	if (SaveGameObject)
	{
		SaveGameObject->bActivated = true;
		SaveSaveGameObject(SaveGameObject);
	}
}

bool UMyGameInstance::IsActivated()
{
	UMySaveGame* SaveGameObject = LoadSaveGameObject();
	if (SaveGameObject)
	{
		return SaveGameObject->bActivated;
	}
	return false;
}

void UMyGameInstance::ShowMainMenu()
{
	if (MainMenuWidget)
	{
		ChangeWidget(MainMenuWidget);
		SetInputModeUIOnly();
	}
}

void UMyGameInstance::ShowEpirationError()
{
	if (ExpirationErrorWidget)
	{
		ChangeWidget(ExpirationErrorWidget);
		SetInputModeUIOnly();
	}
}

void UMyGameInstance::ShowSystemTimeError()
{
	if (SystemTimeErrorWidget)
	{
		ChangeWidget(SystemTimeErrorWidget);
		SetInputModeUIOnly();
	}
}


void UMyGameInstance::SetInputModeUIOnly()
{
	if (CurrentWidget)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(CurrentWidget->GetCachedWidget());

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->SetInputMode(InputMode);
		}
	}
}


UMySaveGame* UMyGameInstance::LoadSaveGameObject()
{
	UMySaveGame* SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameObject->SaveSlotName, SaveGameObject->UserIndex))
	{
		// if there's no save file created
		// Set The first time App installed
		SaveGameObject->ExpirationDate = FDateTime::Now() + FTimespan(NoOfActivationDays, 0, 0, 0);
		UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameObject->SaveSlotName, SaveGameObject->UserIndex);
	}
	else
	{
		// if there's already file save created
		SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameObject->SaveSlotName, SaveGameObject->UserIndex));
	}
	return SaveGameObject;
}

void UMyGameInstance::SaveSaveGameObject(UMySaveGame* SaveGameObject)
{
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameObject->SaveSlotName, SaveGameObject->UserIndex);
}
