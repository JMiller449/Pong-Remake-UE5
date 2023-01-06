// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABoundary.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerController.h"
#include "ScoreBoard_UI.h"
#include "Pong_GM.generated.h"

UCLASS()
class TUTORIAL_PROJECT_API APong_GM : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WidgetArray;

	UScoreBoard_UI* ScoreBoardUI;

	void UpdateAIScore();
	void UpdatePlayerScore();

	UScoreBoard_UI* GetScoreBoard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
