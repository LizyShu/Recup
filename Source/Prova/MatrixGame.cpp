// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova.h"
#include "MatrixGame.h"
#include "MatrixPawn.h"
#include "MGrid.h"
#include "MGrid2.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"



// Sets default values
AMatrixGame::AMatrixGame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetSprite(FirstSprite);
	Sprite->OnInputTouchBegin.AddDynamic(this, &AMatrixGame::OnTouchBegin);
	RootComponent = Sprite;

	ConstructorHelpers::FClassFinder<UUserWidget> Widget (TEXT("WidgetBlueprint'/Game/Blueprints/GameOver.GameOver_C'"));
	if (Widget.Succeeded()) {
		GameOver = Widget.Class;
	}




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
	ChangeSprite();
	//UE_LOG(LogTemp, Warning, TEXT("It works!"));
	
	
	UWorld* World = GetWorld();
	if (World != nullptr) {
	AMatrixPawn* Pawn = Cast<AMatrixPawn>(UGameplayStatics::GetPlayerController(World, 0)->GetControlledPawn());
	}

	if (!OwnerGrid->GetFreeze()) {
		if (OwnerGrid->Verificar(this)) {
			Sprite->SetSprite(ShineSprite);
			OwnerGrid->SetFreeze(true);
			UWorld* World = GetWorld();

			if (World) {
				GetWorldTimerManager().SetTimer(ShowClicked, this, &AMatrixGame::Wait, 0.5f, true);
				Sprite->SetSprite(ShineSprite);
				UE_LOG(LogTemp, Warning, TEXT("Certo!"));
			}
		} else if (World != nullptr) {
			
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
			if (PlayerController && GameOver != NULL) {
				PlayerController->SetPause(true);
				UUserWidget* UserW = UWidgetBlueprintLibrary::Create(World, GameOver, PlayerController);
				if (UserW) {
					UserW->AddToViewport();
				}
			}
				UE_LOG(LogTemp, Warning, TEXT("GameOver!"));
		}
	}
}

/*void AMatrixGame::OnTouchBegin2(ETouchIndex::Type type, UPrimitiveComponent* TouchedComponent) {
	ChangeSprite();

	UWorld* World = GetWorld();
	if (World != nullptr) {
		AMatrixPawn* Pawn = Cast<AMatrixPawn>(UGameplayStatics::GetPlayerController(World, 0)->GetControlledPawn());
	}

	if (!OwnerGrid2->GetFreeze()) {
		if (OwnerGrid2->Verificar2(this)) {
			Sprite->SetSprite(ShineSprite);
			OwnerGrid2->SetFreeze(true);
			UWorld* World = GetWorld();

			if (World) {
				GetWorldTimerManager().SetTimer(ShowClicked, this, &AMatrixGame::Wait2, 0.5f, true);
				Sprite->SetSprite(ShineSprite);
				UE_LOG(LogTemp, Warning, TEXT("Certo!"));
			}
		}
		else if (World != nullptr) {

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
			if (PlayerController && GameOver != NULL) {
				PlayerController->SetPause(true);
				UUserWidget* UserW = UWidgetBlueprintLibrary::Create(World, GameOver, PlayerController);
				if (UserW) {
					UserW->AddToViewport();
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("GameOver!"));
		}
	}
}*/




void AMatrixGame::Wait() {
	Sprite->SetSprite(FirstSprite);
	OwnerGrid->SetFreeze(false);
}

/*void AMatrixGame::Wait2() {
	Sprite->SetSprite(FirstSprite);
	OwnerGrid2->SetFreeze(false);
}*/

