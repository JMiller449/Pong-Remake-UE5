// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABoundary.h"
#include "ScoreBoard_UI.h"
#include "Pong_GM.h"
#include "PongBall.generated.h"

UCLASS()
class TUTORIAL_PROJECT_API APongBall : public AActor
{
	GENERATED_BODY()

	// Defualt Scene Root
	UPROPERTY(VisibleAnywhere, Category = Component);
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = Component);
	class UStaticMeshComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = "Boundary");
	class AABoundary* Boundary;

	UPROPERTY(VisibleAnywhere, Category = Component);
	FVector ChangeInPos;

	UPROPERTY(VisibleAnywhere, Category = Component);
	FVector Direction;

	UPROPERTY(EditAnywhere, Category = Component);
	float Speed;

	UFUNCTION(BlueprintCallable)
		void OnPawnCollision(FVector NewDirection);

	UFUNCTION(BlueprintCallable)
		void OnWallCollision();

	UFUNCTION(BlueprintCallable)
		void OnPlayerGoalCollision();

	UFUNCTION(BlueprintCallable)
		void OnAIGoalCollision();

	UScoreBoard_UI* ScoreBoardUI;

private:
	void GetScoreBoard();

public:	
	// Sets default values for this actor's properties
	APongBall();

	void PublicPawnCollision(FVector NewDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//For add dynamic collisions
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
