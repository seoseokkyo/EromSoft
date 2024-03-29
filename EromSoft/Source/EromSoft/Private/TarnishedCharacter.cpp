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
#include "Though_Sword.h"
#include "CombatComponent.h"
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Animation/AnimMontage.h>
#include <Animation/AnimInstance.h>


ATarnishedCharacter::ATarnishedCharacter()
{
	this->GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny")).Object);

	this->GetMesh()->SetAnimation(ConstructorHelpers::FObjectFinder<UAnimationAsset>(TEXT("/Game/Characters/Mannequins/Animations/ABP_Manny.ABP_Manny")).Object);
}

void ATarnishedCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParam.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
	spawnParam.Owner = this;
	spawnParam.Instigator = this;

	AThough_Sword* equipment = GetWorld()->SpawnActor<AThough_Sword>(AThough_Sword::StaticClass(), GetActorTransform(), spawnParam);

	if (equipment)
	{
		equipment->OnEquipped();
	}
}

void ATarnishedCharacter::Tick(float DeltaTime)
{
	if (bIsSpacebarPressed)
	{
		spacebarPressedTime += DeltaTime;
	}

	CharacterSP_Up(15);
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
		if (DodgeAbleCheck())
		{
			PerformDodge(0, false);

			CharacterSP_Down(20);
		}
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
	// montageIndex가 MainWeapon에 있는 회피 모션 개수보타 크면 0번인덱스, 그렇지 않으면 montageIndex를 씀
	int32 selectedIndex = montageIndex > combatComponent->GetMainWeapon()->dodgeMontages.Num() ? 0 : montageIndex;

	// 랜덤 인덱스 생성
	int32 montagesSize = combatComponent->GetMainWeapon()->dodgeMontages.Num();
	int32 randIndex = FMath::RandRange(0, montagesSize-1);

	// bUseRandomIndex가 true가 들어오면 인덱스를 랜덤으로 생성한것을 사용, 그렇지 않으면 선택된 인덱스 사용
	UAnimMontage* selectedAnimMontage = bUseRandomIndex ? combatComponent->GetMainWeapon()->dodgeMontages[randIndex] : combatComponent->GetMainWeapon()->dodgeMontages[selectedIndex];

	if (IsValid(selectedAnimMontage))
	{
		bIsDodging = true;

		PlayAnimMontage(selectedAnimMontage);

		UE_LOG(LogTemp, Warning, TEXT("Rolled"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PerformDodge - selectedAnimMontage is not Valid"));
	}
}

bool ATarnishedCharacter::DodgeAbleCheck()
{
	bool bAttackCheck = combatComponent->bAttacking;
	bool bTogglingCheck = bIsTogglingCombat;
	bool bIsDodgingCheck = bIsDodging;
	bool bIsDeadCheck = bDead;
	bool bIsDisableCheck = bIsDisable;
	bool bFallingCheck = GetCharacterMovement()->IsFalling();

	if ((bAttackCheck || bTogglingCheck || bIsDodgingCheck || bIsDeadCheck || bIsDisableCheck || bFallingCheck) == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("DodgeAbleCheck - DodgeFailed - State"));
		return false;		
	}

	if (CharacterStatus.currentStamina > 10)
	{
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DodgeAbleCheck - DodgeFailed - Stamina"));
		return false;
	}	
}

void ATarnishedCharacter::ResetCombat_Implementation()
{
	bIsDodging = false;
}
