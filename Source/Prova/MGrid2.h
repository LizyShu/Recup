// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MGrid2.generated.h"

UCLASS()
class PROVA_API AMGrid2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMGrid2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	bool Verificar(class AMatrixGame* Click);
	void SetFreeze(bool NewFreeze);
	bool GetFreeze();

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* Root;
	/*UPROPERTY(EditAnywhere)
	bool bTurned;*/

	TSubclassOf<class AMatrixGame> Um;


	TArray<class AMatrixGame*> Matrix;
	TArray<int> Sequence;

	int Index;
	bool bFreeze;
	bool bLight;
	FTimerHandle MCard;
	int NumOfClicks;


	void Pisca();
	void Show();


	
	
};
