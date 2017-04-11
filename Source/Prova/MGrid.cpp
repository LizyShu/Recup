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
	

	//UE_LOG(LogTemp, Warning, TEXT("Construtor"));

	if (Card01.Succeeded()) {
		Um = Cast<UClass>(Card01.Object);
		//UE_LOG(LogTemp, Warning, TEXT("Foi no cast"));
	}
	
}

// Called when the game starts or when spawned
void AMGrid::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	UE_LOG(LogTemp, Warning, TEXT("Foi no BeginPlay"));
	FActorSpawnParameters SpawnParameters;

	if (World) {

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
		
		
		Pisca();
		
	}
	
	
	
}

// Called every frame
void AMGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMGrid::SetFreeze(bool NewFreeze) {
	bFreeze = NewFreeze;
}

bool AMGrid::GetFreeze() {
	return bFreeze;
}

void AMGrid::Pisca() {

	int Random = FMath::RandRange(0, 2);
	int Random2 = FMath::RandRange(3, 5);
	int Random3 = FMath::RandRange(6, 8);


	//if (!bTurned) {
	if (Random) {
		Sequence.Add(Random);
	}if (Random2) {

		Sequence.Add(Random2);
	}
	if (Random3) {
		Sequence.Add(Random3);
	}


	UWorld* World = GetWorld();
	if (World) {
		Show();
		//GetWorldTimerManager().SetTimer(MCard, this, &AMGrid::Show, 1.0f, true);
		Random++;
	}

}



void AMGrid::Show() {
	
	int ActualSequence = Sequence[Index];
	Matrix[ActualSequence]->ChangeSprite();

	if (bLight) {
		bLight = false;
		GetWorldTimerManager().ClearTimer(MCard);
		Index++;
		if (Index < Sequence.Num()) {
			GetWorldTimerManager().SetTimer(MCard, this, &AMGrid::Show, 1.0f, true);
		}
		else {
			bFreeze = false;
		}
	}
	else {
		bLight = true;
		GetWorldTimerManager().ClearTimer(MCard);
		GetWorldTimerManager().SetTimer(MCard, this, &AMGrid::Show, 1.0f, true);
	}


}

bool AMGrid::Verificar(class AMatrixGame * Click)
{

	if (Sequence[NumOfClicks] == Click->GetIndex()) {
		NumOfClicks++;
		if (NumOfClicks == Sequence.Num()) {
			UWorld* World = GetWorld();
			if (World) {
				APawn* MPawn = UGameplayStatics::GetPlayerController(World, 0)->GetControlledPawn();
				AMatrixPawn* MatrixPawn = Cast<AMatrixPawn>(MPawn);
				MatrixPawn->SetPonto(MatrixPawn->GetPonto() + 100);
				UGameplayStatics::OpenLevel(World, "Mapa2");
				UE_LOG(LogTemp, Warning, TEXT("Foi Level 2!"));

			}
		}
		return true;
	}


	return false;
}

void AMGrid::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if ((OtherActor != nullptr) && (OtherActor->IsA(AMatrixPawn::StaticClass()))) {
		AMatrixPawn* Grid = Cast<AMatrixPawn>(OtherActor);
		UWorld* World = GetWorld();
		if (Grid->GetPonto() == 100 && World != nullptr) {
			UGameplayStatics::OpenLevel(World, "Mapa2");
			UE_LOG(LogTemp, Warning, TEXT("Pox. Level"));
		}
	}
}




