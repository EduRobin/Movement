// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Camera Rotation");
	SpringArmComponent->SetupAttachment(RootComponent);

	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);

	TurnSideRate = 50;
	LookUpRate = 50;
	

	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Forward", this, &AMyCharacter::Move);
	PlayerInputComponent->BindAxis("Side", this, &AMyCharacter::Side);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnSide", this, &AMyCharacter::TurnSide);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
}

void AMyCharacter::Move(float Direction)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator Yaw(0,Rotation.Yaw,0);
	FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
	AddMovementInput(direction, Direction);
}

void AMyCharacter::Side(float Direction)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator Yaw(0,Rotation.Yaw,0);
	FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
	AddMovementInput(direction, Direction);
}

void AMyCharacter::LookUp(float Rate)
{
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds()*LookUpRate);
}

void AMyCharacter::TurnSide(float Rate)
{
	AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds()*TurnSideRate);
}

