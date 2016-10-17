// Fill out your copyright notice in the Description page of Project Settings.

#include "Park.h"
#include "MySaveGame.h"

UMySaveGame::UMySaveGame()
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
	bActivated = false;
	FDateTime LastDateTime(0);// = FDateTime(0);
	FDateTime ExpirationDate(0);
}


