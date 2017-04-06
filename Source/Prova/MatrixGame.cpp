// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova.h"
#include "MatrixGame.h"
#include "MatrixPawn.h"
#include "MGrid.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"


// Sets default values
AMatrixGame::AMatrixGame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetSprite(FirstSprite);
	Sprite->OnInputTouchBegin.AddDynamic(this, &AMatrixGame::OnTouchBegin);
	RootComponent = Sprite;


}

// Called when the game starts or when spawned
void AMatrixGame::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMatrixGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMatrixGame::SetIndex(int NewIndex) {
	Index = NewIndex;
}

int AMatrixGame::GetIndex() {
	return Index;
}

void AMatrixGame::ChangeSprite() {
	if (Sprite->GetSprite() == FirstSprite) {
		Sprite->SetSprite(ShineSprite);
	}
	else {
		Sprite->SetSprite(FirstSprite);
	}
}

void AMatrixGame::SetOwnerGrid(class AMGrid* Grid) {
	OwnerGrid = Grid;
}

void AMatrixGame::SetOwnerGrid2(class AMGrid2* Grid2) {
	OwnerGrid2 = Grid2;
}

void AMatrixGame::OnTouchBegin(ETouchIndex::Type type, UPrimitiveComponent* TouchedComponent) {
	UE_LOG(LogTemp, Warning, TEXT("It works!"));

	/*UWorld* World = GetWorld();
	if (World != nullptr) {
	AMatrixPawn* Pawn = Cast<AMatrixPawn>(UGameplayStatics::GetPlayerController(World, 0)->GetControlledPawn());
	}*/

	if (!OwnerGrid->GetFreeze()) {
		if (OwnerGrid->Verificar(this)) {
			Sprite->SetSprite(FirstSprite);
			OwnerGrid->SetFreeze(true);
			UWorld* World = GetWorld();

			if (World) {
				GetWorldTimerManager().SetTimer(ShowClicked, this, &AMatrixGame::Wait, 0.5f, true);

			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("GameOver!"));
			
		}
	}
}

void AMatrixGame::Wait() {
	Sprite->SetSprite(ShineSprite);
	OwnerGrid->SetFreeze(false);
}

