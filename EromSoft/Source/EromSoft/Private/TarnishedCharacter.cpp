// Fill out your copyright notice in the Description page of Project Settings.


#include "TarnishedCharacter.h"
//#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


void ATarnishedCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

void ATarnishedCharacter::Tick(float DeltaTime)
{
	if (bIsSpacebarPressed)
	{
		spacebarPressedTime += DeltaTime;
	}
}

void ATarnishedCharacter::InitializeCharacterStatus()
{
	CharacterStatus.CharacterName = L"Tarnished";
	CharacterStatus.strength = 10;
	CharacterStatus.endurance = 10;
	CharacterStatus.AddedHealthPoint = 10;
	CharacterStatus.AddedStaminaPoint = 10;

	CharacterStatus.maxHealth = 100 + (CharacterStatus.AddedHealthPoint * 10);
	CharacterStatus.maxMana = 100 + (CharacterStatus.AddedManaPoint * 10);
	CharacterStatus.maxStamina = 100 + (CharacterStatus.AddedStaminaPoint * 10);

	CharacterStatus.currentHealth = CharacterStatus.maxHealth;
	CharacterStatus.currentMana = CharacterStatus.maxMana;
	CharacterStatus.currentStamina = CharacterStatus.maxStamina;

	UE_LOG(LogTemp, Warning, TEXT("Name		:	%s"), *CharacterStatus.CharacterName);
	UE_LOG(LogTemp, Warning, TEXT("Str		:	%d"), CharacterStatus.strength);
	UE_LOG(LogTemp, Warning, TEXT("Endu		:	%d"), CharacterStatus.endurance);
	UE_LOG(LogTemp, Warning, TEXT("MaxHP	:	%d"), CharacterStatus.maxHealth);
	UE_LOG(LogTemp, Warning, TEXT("MaxHP	:	%d"), CharacterStatus.maxStamina);
}


void ATarnishedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Spacebar(Walk,Run / Rolling)
		EnhancedInputComponent->BindAction(SpacebarAction, ETriggerEvent::Started, this, &ATarnishedCharacter::SpacebarPressed);
		EnhancedInputComponent->BindAction(SpacebarAction, ETriggerEvent::Completed, this, &ATarnishedCharacter::SpacebarReleased);


		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ATarnishedCharacter::SpacebarReleased);
		EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Completed, this, &ATarnishedCharacter::SpacebarReleased);
		EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Completed, this, &ATarnishedCharacter::SpacebarReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}

void ATarnishedCharacter::SpacebarPressed(const FInputActionValue& Value)
{
	this->bIsSpacebarPressed = true;
	spacebarPressedTime = 0.f;

	this->GetCharacterMovement()->MaxWalkSpeed = 700;
}

void ATarnishedCharacter::SpacebarReleased(const FInputActionValue& Value)
{
	this->bIsSpacebarPressed = false;

	if (spacebarPressedTime < 0.2)
	{
		UE_LOG(LogTemp, Warning, TEXT("����� �������ϴ�."));
		// ������ ����

	}

	this->GetCharacterMovement()->MaxWalkSpeed = 300;
}

bool ATarnishedCharacter::CheckPerformToggleCombatMotion()
{
	return false;
}

bool ATarnishedCharacter::CheckPerformAttack()
{
	return false;
}

bool ATarnishedCharacter::CheckPerformDodge()
{
	return false;
}

void ATarnishedCharacter::PerformAttack(int32 attackIndex, bool bUseRandomIndex)
{
}

void ATarnishedCharacter::PerformDodge(int32 montageIndex, bool bUseRandomIndex)
{
}
