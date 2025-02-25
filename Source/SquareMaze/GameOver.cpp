// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Timer.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ScoreSave.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	GetTime();

	CharacterStop();
}

void UGameOver::GetTime()
{
	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UTimer::StaticClass(), false);

	if (Widgets.Num() > 0)
	{
		UTimer* TimerWidget = Cast<UTimer>(Widgets[0]);
        
		if (TimerWidget)
		{
			TimerWidget->StopTimer();
			float CurrentTime = TimerWidget->ElapsedMilliseconds;
			FString SetTime = TimerWidget->GameOverTimer;
			TimerText->SetText(FText::FromString(SetTime));
			UE_LOG(LogTemp, Warning, TEXT("현재 타이머 값: %f"), CurrentTime);

			UScoreSave* Score = Cast<UScoreSave>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerScoreSlot"), 0));

			if (!Score)
			{
				Score = Cast<UScoreSave>(UGameplayStatics::CreateSaveGameObject(UScoreSave::StaticClass()));
				UGameplayStatics::SaveGameToSlot(Score, TEXT("PlayerScoreSlot"), 0);
			}
			
			bool result = false;
			// Score에 따른 최고 기록 달성 텍스트 표시
			if (Score)
			{
				result = Score->ScoreComparison(CurrentTime);
			}
			if (result)
			{
				UE_LOG(LogTemp, Warning, TEXT("최고 기록 달성"));
				BestText->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("최고 기록 실패"));
				BestText->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("타이머 위젯을 찾을 수 없음"));
	}
}

void UGameOver::CharacterStop()
{
	APawn* PlayerPawn = GetOwningPlayerPawn();
    
	if (PlayerPawn)
	{
		// 만약 PlayerPawn이 ACharacter라면
		ACharacter* Character = Cast<ACharacter>(PlayerPawn);
		if (Character)
		{
			// 캐릭터의 MovementComponent를 가져옵니다.
			UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
			if (MovementComponent)
			{
				// 캐릭터의 이동 속도를 0으로 설정하여 이동을 멈춥니다.
				MovementComponent->MaxWalkSpeed = 0.f;
			}
		}
	}
}



