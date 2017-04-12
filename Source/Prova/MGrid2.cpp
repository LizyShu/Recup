// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova.h"
#include "MGrid2.h"
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
AMGrid2::AMGrid2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	ConstructorHelpers::FObjectFinder<UClass> Card01(TEXT("Blueprint'/Game/Blueprints/Card01.Card01_C'"));

	if (Card01.Succeeded()) {
		Um = Cast<UClass>(Card01.Object);
	}

}

// Called when the game starts or when spawned
void AMGrid2::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		AMatrixGame* C1 = World->SpawnActor<AMatrixGame>(Um, FVector(1000.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C2 = World->SpawnActor<AMatrixGame>(Um, FVector(1000.0f, 0.0f, 200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C3 = World->SpawnActor<AMatrixGame>(Um, FVector(1000.0f, 0.0f, -200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C4 = World->SpawnActor<AMatrixGame>(Um, FVector(800.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C5 = World->SpawnActor<AMatrixGame>(Um, FVector(800.0f, 0.0f, 200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C6 = World->SpawnActor<AMatrixGame>(Um, FVector(800.0f, 0.0f, -200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C7 = World->SpawnActor<AMatrixGame>(Um, FVector(600.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C8 = World->SpawnActor<AMatrixGame>(Um, FVector(600.0f, 0.0f, 200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C9 = World->SpawnActor<AMatrixGame>(Um, FVector(600.0f, 0.0f, -200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C10 = World->SpawnActor<AMatrixGame>(Um, FVector(400.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C11 = World->SpawnActor<AMatrixGame>(Um, FVector(400.0f, 0.0f, 200.0f), FRotator::ZeroRotator, SpawnParameters);
		AMatrixGame* C12 = World->SpawnActor<AMatrixGame>(Um, FVector(400.0f, 0.0f, -200.0f), FRotator::ZeroRotator, SpawnParameters);
	

		C1->SetIndex(0);
		C2->SetIndex(1);
		C3->SetIndex(2);
		C4->SetIndex(3);
		C5->SetIndex(4);
		C6->SetIndex(5);
		C7->SetIndex(6);
		C8->SetIndex(7);
		C9->SetIndex(8);
		C10->SetIndex(9);
		C11->SetIndex(10);
		C12->SetIndex(11);
		

		C1->SetOwnerGrid2(this);
		C2->SetOwnerGrid2(this);
		C3->SetOwnerGrid2(this);
		C4->SetOwnerGrid2(this);
		C5->SetOwnerGrid2(this);
		C6->SetOwnerGrid2(this);
		C7->SetOwnerGrid2(this);
		C8->SetOwnerGrid2(this);
		C9->SetOwnerGrid2(this);
		C10->SetOwnerGrid2(this);
		C11->SetOwnerGrid2(this);
		C12->SetOwnerGrid2(this);
		

		Matrix.Add(C1);
		Matrix.Add(C2);
		Matrix.Add(C3);
		Matrix.Add(C4);
		Matrix.Add(C5);
		Matrix.Add(C6);
		Matrix.Add(C7);
		Matrix.Add(C8);
		Matrix.Add(C9);
		Matrix.Add(C10);
		Matrix.Add(C11);
		Matrix.Add(C12);
	


		Pisca();

	}

}

// Called every frame
void AMGrid2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMGrid2::SetFreeze(bool NewFreeze) {
	bFreeze = NewFreeze;
}

bool AMGrid2::GetFreeze() {
	return bFreeze;
}

void AMGrid2::Pisca() {

	int Random = FMath::RandRange(0, 11);
	int Random2 = FMath::RandRange(0, 11);
	int Random3 = FMath::RandRange(0, 11);
	int Random4 = FMath::RandRange(0, 11);


	//if (!bTurned) {
	if (Random) {
		Sequence.Add(Random);
	}if (Random2 != Random) {
		Sequence.Add(Random2);
	}
	if (Random3 != Random2 != Random) {
		Sequence.Add(Random3);
	}
	if (Random4 != Random3 != Random2 != Random) {
		Sequence.Add(Random4);
	}



	UWorld* World = GetWorld();
	if (World) {
		Show();
		Random++;

	}

}



void AMGrid2::Show() {

	int ActualSequence = Sequence[Index];
	Matrix[ActualSequence]->ChangeSprite();

	if (bLight) {
		bLight = false;
		GetWorldTimerManager().ClearTimer(MCard);
		Index++;
		if (Index < Sequence.Num()) {
			GetWorldTimerManager().SetTimer(MCard, this, &AMGrid2::Show, 1.0f, true);
		}
		else {
			bFreeze = false;
		}
	}
	else {
		bLight = true;
		GetWorldTimerManager().ClearTimer(MCard);
		GetWorldTimerManager().SetTimer(MCard, this, &AMGrid2::Show, 1.0f, true);
	}


}

bool AMGrid2::Verificar2(class AMatrixGame * Click)
{

	if (Sequence[NumOfClicks] == Click->GetIndex()) {
		NumOfClicks++;
		if (NumOfClicks == Sequence.Num()) {
			UWorld* World = GetWorld();
			if (World) {
				APawn* MPawn = UGameplayStatics::GetPlayerController(World, 0)->GetControlledPawn();
				AMatrixPawn* MatrixPawn = Cast<AMatrixPawn>(MPawn);
				MatrixPawn->SetPonto(MatrixPawn->GetPonto() + 100);
				//UGameplayStatics::OpenLevel(World, "Mapa3");
				//UE_LOG(LogTemp, Warning, TEXT("Foi Level 3!"));
			}
		}
		return true;
	}
	return false;
}

