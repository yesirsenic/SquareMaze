// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "SpeedBoost.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComponent;
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						   bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (Player)
	{
		USpeedBoost* SpeedBoostComp = Player->FindComponentByClass<USpeedBoost>();
		if (SpeedBoostComp)
		{
			SpeedBoostComp->ActiveSpeedBoost();
		}
		PlayCoinSound();
		Destroy(); // 코인 삭제
	}
}

void ACoin::PlayCoinSound()
{
	if (Sound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Sound);
	}
}


