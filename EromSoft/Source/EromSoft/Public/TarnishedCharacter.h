// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EromSoftCharacter.h"

#include "TarnishedCharacter.generated.h"

/**
 * 
 */

class ABaseEquippable;
class ABaseWeapon;
class AThough_Sword;

UCLASS()
class EROMSOFT_API ATarnishedCharacter : public AEromSoftCharacter
{
	GENERATED_BODY()
	
	/** Spacebar Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpacebarAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** LightAttack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LightAttackAction;

	/** ToggleCombat Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleCombatAction;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	void InitializeCharacterStatus() override;

public:

	ATarnishedCharacter();

	// Variables
	bool bIsTogglingCombat = false;
	bool bIsDodging = false;
	bool bDead = false;
	bool bIsDisable = false;

	// Functions

	// Walk&Run / Rolling Function
	bool bIsSpacebarPressed = false;
	
	float spacebarPressedTime = 0.0f;
	void SpacebarPressed(const FInputActionValue& Value);
	void SpacebarReleased(const FInputActionValue& Value);

	// Combat State Toggle
	

	bool CheckPerformToggleCombatMotion();
	bool CheckPerformAttack();
	bool CheckPerformDodge();
	void PerformAttack(int32 attackIndex, bool bUseRandomIndex);
	void PerformDodge(int32 montageIndex, bool bUseRandomIndex);

	bool DodgeAbleCheck();
};
