// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

/**
 * 
 */
UCLASS()
class SQUAREMAZE_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BestText;
	
	UPROPERTY(EditAnywhere, Category="UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TimerWidgetClass;
	
	void GetTime();

	void CharacterStop();

	
	
};
