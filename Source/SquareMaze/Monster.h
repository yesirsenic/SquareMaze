// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Monster.generated.h"

UCLASS()
class SQUAREMAZE_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UBoxComponent* CollisionComponent;

private:
	UPROPERTY(EditDefaultsOnly,Category="Monster" , meta = (AllowPrivateAccess = "true"))
	TArray<FVector> WayPoints;

	UPROPERTY(EditAnywhere,Category="Monster" , meta = (AllowPrivateAccess = "true"))
	float Speed = 600.f;

	int CurrentTargetIndex = 3;

	FTimerHandle TimerHandle;

	void MoveTarget(float Deltatime);

	void AddSpeed();

	void GameOverPopupSet();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, Category="UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WidgetClass;
	
	UUserWidget* CreatedWidget;

	bool Is_Move = true;
};
