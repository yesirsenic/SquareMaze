// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PassPoint.generated.h"


UCLASS()
class SQUAREMAZE_API APassPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APassPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* CollisionBox;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlapedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBoxIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> PlayerBP;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	AActor* BackSpawnCoin;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	AActor* StartSpawnCoin;
	

	
	

};
