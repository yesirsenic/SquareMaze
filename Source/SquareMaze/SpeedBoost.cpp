// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
USpeedBoost::USpeedBoost()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USpeedBoost::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		OriginSpeed = OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed;
	}
	
}

void USpeedBoost::ActiveSpeedBoost()
{
	if (!GetOwner()) return;

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	if (bIsSpeedBoosted)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Speed Boost Reset"));
		GetWorld()->GetTimerManager().ClearTimer(SpeedBoostTimer);
		GetWorld()->GetTimerManager().SetTimer(SpeedBoostTimer, this, &USpeedBoost::ResetSpeed, SpeedDuration, false);
	}
	else
	{
		// 부스트 상태가 아닐 경우 부스트 활성화 및 타이머 시작
		bIsSpeedBoosted = true;
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = BoostSpeed;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Speed Boost Reset"));
		GetWorld()->GetTimerManager().ClearTimer(SpeedBoostTimer);
		GetWorld()->GetTimerManager().SetTimer(SpeedBoostTimer, this, &USpeedBoost::ResetSpeed, SpeedDuration, false);
	}
}

void USpeedBoost::ResetSpeed()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed != OriginSpeed)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = OriginSpeed;
	}

	bIsSpeedBoosted = false;
}




