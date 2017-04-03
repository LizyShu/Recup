// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova.h"
#include "MGrid.h"
#include "MatrixGame.h"
#include "MatrixPawn.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"


// Sets default values
AMGrid::AMGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	ConstructorHelpers::FObjectFinder<UClass> Card1(TEXT("Blueprint'/Game/Blueprints/Card1.Card1_C'"));

	if (Card1.Succeeded()) {
		Um = Cast<UClass>(Card1.Object);
	}

}

// Called when the game starts or when spawned
void AMGrid::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		AMatrixGame* Card1 = World->SpawnActor<AMatrixGame>(Um , FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);

		Card1->SetIndex(0);

		Card1->SetOwnerGrid(this);

		Matrix.Add(Card1);

	}
}

// Called every frame
void AMGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

