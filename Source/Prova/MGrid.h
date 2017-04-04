// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MGrid.generated.h"

UCLASS()
class PROVA_API AMGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool Verificar(class AMatrixGame* Click);

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	TSubclassOf<class AMatrixGame> Um;
	

	TArray<class AMatrixGame*> Matrix;

	int index;

	void Show();
	
};
