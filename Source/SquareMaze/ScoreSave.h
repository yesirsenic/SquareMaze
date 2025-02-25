// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScoreSave.generated.h"

/**
 * 
 */
UCLASS()
class SQUAREMAZE_API UScoreSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UScoreSave();
	
	UPROPERTY(VisibleAnywhere, Category = "ScoreSave")
	int32 TimeScore;

	bool ScoreComparison(int32 Score);
};
