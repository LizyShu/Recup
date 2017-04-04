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
	ConstructorHelpers::FObjectFinder<UClass> Card01(TEXT("Blueprint'/Game/Blueprints/Card01.Card01_C'"));
	

	UE_LOG(LogTemp, Warning, TEXT("Construtor"));

	if (Card01.Succeeded()) {
		Um = Cast<UClass>(Card01.Object);
		UE_LOG(LogTemp, Warning, TEXT("Foi no cast"));
	}
	
}

// Called when the game starts or when spawned
void AMGrid::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	UE_LOG(LogTemp, Warning, TEXT("Foi no BeginPlay"));
	if (World) {
		FActorSpawnParameters SpawnParameters;
		AMatrixGame* C1 = World->SpawnActor<AMatrixGame>(Um, FVector(1000.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		/*if (C1 != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Foi no c1"));
		}*/
		AMatrixGame* C2 = World->SpawnActor<AMatrixGame>(Um, FVector(1000.0f, 0.0f, 200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C3 = World->SpawnActor<AMatrixGame>(Um, FVector(1000.0f, 0.0f, -200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C4 = World->SpawnActor<AMatrixGame>(Um, FVector(800.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C5 = World->SpawnActor<AMatrixGame>(Um, FVector(800.0f, 0.0f, 200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C6 = World->SpawnActor<AMatrixGame>(Um, FVector(800.0f, 0.0f, -200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C7 = World->SpawnActor<AMatrixGame>(Um, FVector(600.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C8 = World->SpawnActor<AMatrixGame>(Um, FVector(600.0f, 0.0f, 200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C9 = World->SpawnActor<AMatrixGame>(Um, FVector(600.0f, 0.0f, -200.0f), FRotator::ZeroRotator, SpawnParameters);

		C1->SetIndex(0);
		C2->SetIndex(1);
		C3->SetIndex(2);
		C4->SetIndex(3);
		C5->SetIndex(4);
		C6->SetIndex(5);
		C7->SetIndex(6);
		C8->SetIndex(7);
		C9->SetIndex(8);

		C1->SetOwnerGrid(this);
		C2->SetOwnerGrid(this);
		C3->SetOwnerGrid(this);
		C4->SetOwnerGrid(this);
		C5->SetOwnerGrid(this);
		C6->SetOwnerGrid(this);
		C7->SetOwnerGrid(this);
		C8->SetOwnerGrid(this);
		C9->SetOwnerGrid(this);

		Matrix.Add(C1);
		Matrix.Add(C2);
		Matrix.Add(C3);
		Matrix.Add(C4);
		Matrix.Add(C5);
		Matrix.Add(C6);
		Matrix.Add(C7);
		Matrix.Add(C8);
		Matrix.Add(C9);
	}

}

// Called every frame
void AMGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMGrid::Show() {
	

}

bool AMGrid::Verificar(AMatrixGame * Click)
{


	return false;
}

