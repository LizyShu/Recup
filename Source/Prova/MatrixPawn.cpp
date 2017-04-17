// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova.h"
#include "MatrixPawn.h"


// Sets default values
AMatrixPawn::AMatrixPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Camera = CreateDefaultSubobject<UCameraComponent>
		(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 2048.0f;
	Camera->SetupAttachment(RootComponent);
	AutoPossessPlayer = EAutoReceiveInput::Player0;



}

// Called when the game starts or when spawned
void AMatrixPawn::BeginPlay()
{
	Super::BeginPlay();
	//Ponto;
	
}

// Called every frame
void AMatrixPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMatrixPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Save", IE_Pressed, this, &AMatrixPawn::SaveGame);
	InputComponent->BindAction("Save", IE_Pressed, this, &AMatrixPawn::LoadGame);

}

void AMatrixPawn::SetPonto(int NewPonto) {
	Ponto = NewPonto;
}

int AMatrixPawn::GetPonto() {
	return Ponto;
}

void AMatrixPawn::SaveGame() {
	UE_LOG(LogTemp, Warning, TEXT("SaveGame"));
	UMySaveGame*SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance->PlayerName = "ggg";
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	UE_LOG(LogTemp, Warning, TEXT("Game Saved"));

}
void AMatrixPawn::LoadGame() {
	UE_LOG(LogTemp, Warning, TEXT("LoadGame"));
	UMySaveGame*LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	FString Nome = LoadGameInstance->PlayerName;
	UE_LOG(LogTemp, Warning, TEXT("PlayerName: %s"), Nome);
}

