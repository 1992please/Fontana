// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PARK_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
		UMySaveGame();
public:
	
		UPROPERTY()
		FString SaveSlotName;

	UPROPERTY()
		uint32 UserIndex;

	UPROPERTY()
		bool bActivated;

	UPROPERTY()
		FDateTime LastDateTime;

	UPROPERTY()
		FDateTime ExpirationDate;
	
};
