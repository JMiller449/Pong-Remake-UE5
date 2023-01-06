// Available for free use - Original Author Joseph Miller

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.h"
#include "PongAI.generated.h"

UCLASS()
class TUTORIAL_PROJECT_API APongAI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APongAI();

	// Defualt Scene Root
	UPROPERTY(VisibleAnywhere, Category = Component);
	class USceneComponent* DefaultSceneRoot;

	// Declares Components
	UPROPERTY(VisibleAnywhere, Category = Component);
	class UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, Category = Component);
	class UBoxComponent* BodyCollider;

	UPROPERTY(VisibleAnywhere, Category = Component);
	class APongBall* Ball;

	// Declares AI navigation variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LineTrace");
	float CurrYSearchValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTrace");
	float InitYSearchValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LineTrace");
	float CurrDistance = 0.0f;

	// AI movement function
	UFUNCTION(BlueprintCallable)
		void Move();

	// Function to handle finding the PongBall in the level
	UFUNCTION(BlueprintCallable)
		void FindBall();

	// Overlap Function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Remembers if PongBall variable has been assigned (enables AI movement)
	UPROPERTY()
	bool bFoundBall;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//For add dynamic collisions
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
