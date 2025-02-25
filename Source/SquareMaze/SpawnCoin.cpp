// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnCoin.h"

// Sets default values
ASpawnCoin::ASpawnCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void ASpawnCoin::SpawnCoinRandom()
{
	
	float RandomX = FMath::RandRange(MinSpawnPointX / SpawnIntervalX, MaxSpawnPointX / SpawnIntervalX );
	float RandomY = FMath::RandRange(MinSpawnPointY / SpawnIntervalY, MaxSpawnPointY / SpawnIntervalY);
	float RandomZ = FMath::RandRange(MinSpawnPointZ / SpawnIntervalZ, MaxSpawnPointZ / SpawnIntervalZ);

	RandomX *= SpawnIntervalX;
	RandomY *= SpawnIntervalY;
	RandomZ *= SpawnIntervalZ;

	FVector SpawnPoint = FVector(RandomX, RandomY, RandomZ);

	FRotator SpawnRotator = FRotator::ZeroRotator;

	if (Is_Vertical)
		SpawnRotator = FRotator(0,90,0);


	SpawnedCoin = GetWorld()->SpawnActor<AActor>(SpawnCoin,SpawnPoint, SpawnRotator);
	
}


