// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EromSoftCharacter.h"
#include "TarnishedCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EROMSOFT_API ATarnishedCharacter : public AEromSoftCharacter
{
	GENERATED_BODY()
	
	/** Spacebar Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpacebarAction;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	void InitializeCharacterStatus() override;

	// Walk&Run / Rolling Function
	bool bIsSpacebarPressed = false;
	float spacebarPressedTime = 0.0f;
	void SpacebarPressed(const FInputActionValue& Value);
	void SpacebarReleased(const FInputActionValue& Value);

};
