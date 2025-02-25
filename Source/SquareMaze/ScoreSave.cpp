// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreSave.h"
#include "Kismet/GameplayStatics.h"

UScoreSave::UScoreSave()
{
	TimeScore = 0;
}


bool UScoreSave::ScoreComparison(int32 Score)
{
	UScoreSave* SaveInstance = Cast<UScoreSave>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerScoreSlot"), 0));
	
	if (!SaveInstance)
	{
		SaveInstance = Cast<UScoreSave>(UGameplayStatics::CreateSaveGameObject(UScoreSave::StaticClass()));
		UGameplayStatics::SaveGameToSlot(SaveInstance, TEXT("PlayerScoreSlot"), 0);
		if (!SaveInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("SaveGame 객체 생성 실패"));
			return false;
		}
	}

	if (SaveInstance->TimeScore < Score)
	{
		SaveInstance->TimeScore = Score;
		UE_LOG(LogTemp, Warning, TEXT("현재 기록: %d"), SaveInstance->TimeScore);
		UGameplayStatics::SaveGameToSlot(SaveInstance, TEXT("PlayerScoreSlot"), 0);
		return true;
	}

	return false;
}

