// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Timer.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = nullptr;
	CreatedWidget = nullptr;

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	if (WayPoints.Num() != 0)
	{
		SetActorLocation(WayPoints[CurrentTargetIndex]);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AMonster::AddSpeed,1.0f,true);

	CollisionComponent = FindComponentByClass<UBoxComponent>();

	if (CollisionComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionComponent 가져옴!"));
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnOverlapBegin);
	}
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Is_Move)
	{
		MoveTarget(DeltaTime);
	}
	

}

void AMonster::MoveTarget(float Deltatime)
{
	if (WayPoints.Num() == 0)
		return;

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = WayPoints[CurrentTargetIndex];

	float distance = FVector::Dist(CurrentLocation, TargetLocation);

	if (distance< 10.0f)
	{
		CurrentTargetIndex = (CurrentTargetIndex + 1) % WayPoints.Num();
	}

	else
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, Deltatime, Speed);
		SetActorLocation(NewLocation);
	}
}

void AMonster::AddSpeed()
{
	Speed+= 10;
}

void AMonster::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (Player)
	{
		GameOverPopupSet();

		Is_Move = false;
		
	}
}

void AMonster::GameOverPopupSet()
{
	UE_LOG(LogTemp, Warning, TEXT("부딪힘!!!"))
		
	if (!WidgetClass) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;
		
	CreatedWidget = CreateWidget<UUserWidget>(PC, WidgetClass);

	if (CreatedWidget)
	{
		CreatedWidget->AddToViewport();
	}
}





