// Fill out your copyright notice in the Description page of Project Settings.


#include "PassPoint.h"

#include "Coin.h"
#include "SpawnCoin.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APassPoint::APassPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APassPoint::OnOverlap);
}

// Called when the game starts or when spawned
void APassPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APassPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APassPoint::OnOverlap(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBoxIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->IsA(*PlayerBP))
		{
			ASpawnCoin* StartCoin = Cast<ASpawnCoin>(StartSpawnCoin);

			TArray<AActor*> FoundCoins;
					
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoin::StaticClass(), FoundCoins);
			for (AActor* Actor : FoundCoins)
			{
				if (Actor) 
				{
					Actor->Destroy();
				}
			}
			
			

			if (StartCoin)
			{
				StartCoin->SpawnCoinRandom();
			}

			
			
		}
	}
	
}


