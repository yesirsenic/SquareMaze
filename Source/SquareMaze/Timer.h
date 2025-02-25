// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Timer.generated.h"

/**
 * 
 */
UCLASS()
class SQUAREMAZE_API UTimer : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void StartTimer();
	
	UFUNCTION(BlueprintCallable)
	void UpdateTime();

	UFUNCTION(BlueprintCallable)
	void StopTimer();

	FString GameOverTimer = "0";
	
	int32 ElapsedMilliseconds = 0;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerText;

	FTimerHandle TimerHandle;

	
	
};
