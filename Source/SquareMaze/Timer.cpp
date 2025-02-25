// Fill out your copyright notice in the Description page of Project Settings.


#include "Timer.h"
#include "Components/TextBlock.h"

void UTimer::NativeConstruct()
{
	Super::NativeConstruct();
	
	StartTimer();
}

void UTimer::StartTimer()
{
	ElapsedMilliseconds = 0;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTimer::UpdateTime, 0.01f, true);
}

void UTimer::StopTimer()
{
	GameOverTimer = TimerText->GetText().ToString();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}


void UTimer::UpdateTime()
{
	if (!TimerText) return;

	ElapsedMilliseconds += 10;
	int32 TotalSeconds = ElapsedMilliseconds / 1000;
	int32 Minutes = TotalSeconds / 60;
	int32 Seconds = TotalSeconds % 60;
	int32 Milliseconds = ElapsedMilliseconds % 1000;

	FString CurrentTime = FString::Printf(TEXT("%02d:%02d:%02d"), Minutes, Seconds, Milliseconds/10);
	
	TimerText->SetText(FText::FromString(CurrentTime));
}