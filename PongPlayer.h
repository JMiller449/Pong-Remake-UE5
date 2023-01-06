// Available for free use - Original Author Joseph Miller

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongPlayer.generated.h"

UCLASS()
class TUTORIAL_PROJECT_API APongPlayer : public APawn
{
	GENERATED_BODY()

	// Defualt Scene Root
	UPROPERTY(VisibleAnywhere, Category = Component);
	class USceneComponent* DefaultSceneRoot;

	// Declaring components
	UPROPERTY(EditAnywhere, Category = Component);
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Component);
	class UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, Category = Component);
	class UBoxComponent* BodyCollider;
	
	// Overlap Function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Variables to handle movement
	bool bMoveUp;
	bool bCollideTop;
	void MoveUp();
	void StopUp();

	bool bMoveDown;
	bool bCollideBot;
	void MoveDown();
	void StopDown();

public:
	// Sets default values for this pawn's properties
	APongPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//For add dynamic collisions
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
