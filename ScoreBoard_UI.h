// Available for free use - Original Author Joseph Miller

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreBoard_UI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOverSignature, bool, bWon);

UCLASS()
class TUTORIAL_PROJECT_API UScoreBoard_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	// UI Components
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* Canvas;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AIScore;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerScore;

	// Score update handler functions
	void AIScored();
	void PlayerScored();

	UPROPERTY()
	float AIScoreNum;

	UPROPERTY()
	float PlayerScoreNum;

	// Called on game over
	UPROPERTY(BlueprintAssignable)
		FOnGameOverSignature OnGameOver;
	
protected:
	// Sets default variable values
	virtual void NativeConstruct() override;
};
