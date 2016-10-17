// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"
class UUserWidget;
/**
 * 
 */
UCLASS()
class PARK_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UI")
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowMainMenu();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowSystemTimeError();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowEpirationError();

	UFUNCTION(BlueprintCallable, Category = "AdminSys")
	void CheckActivationState();

	UFUNCTION(BlueprintCallable, Category = "AdminSys")
	void Activate();

	UFUNCTION(BlueprintCallable, Category = "AdminSys")
	bool IsActivated();

protected:

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> SystemTimeErrorWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> ExpirationErrorWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	int NoOfActivationDays;

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
	UUserWidget* CurrentWidget;

private:
	void SetInputModeUIOnly();

	class UMySaveGame* LoadSaveGameObject();

	void SaveSaveGameObject(class UMySaveGame* SaveGameObject);

};
