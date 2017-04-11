// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MatrixGame.generated.h"

UCLASS()
class PROVA_API AMatrixGame : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMatrixGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetIndex(int NewIndex);
	int GetIndex();
	void ChangeSprite();
	void SetOwnerGrid(class AMGrid* Grid);
	void SetOwnerGrid2(class AMGrid2* Grid2);



private:

	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* Sprite;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* FirstSprite;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* ShineSprite;

		TSubclassOf<class UUserWidget> GameOver;


		class AMGrid* OwnerGrid;
		class AMGrid2* OwnerGrid2;


	UPROPERTY(EditAnywhere)
		int Index;
	FTimerHandle ShowClicked;

	
	UFUNCTION()
		void OnTouchBegin(ETouchIndex::Type type, UPrimitiveComponent* TouchedComponent);

	void Wait();

	
};
