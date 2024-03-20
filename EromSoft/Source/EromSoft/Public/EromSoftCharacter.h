// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CharacterStatusStruct.h"
#include "EromSoftDef.h"
#include "EromSoftCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_DELEGATE(FCharacterStatChanged);
//DECLARE_DYNAMIC_DELEGATE(FCharacterDead);

UCLASS(config=Game)
class AEromSoftCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	FCharacterStat CharacterStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	FCharacterStatChanged	CharacterStatChangedDeligate;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	//FCharacterDead			CharacterDeadDeligate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	bool bIsNeedToSpawn;

public:
	AEromSoftCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	//virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void InitializeCharacterStatus() PURE_VIRTUAL(AEromSoftCharacter::InitializeCharacterStatus, return;);


	// Character Hp,Mp,Sp Changed
	void CharacterStatusChanged(ECharacterStatusType eType, int32 Value);

	UFUNCTION(BlueprintCallable)
	void CharacterHP_Up(int32 UpValue);
	UFUNCTION(BlueprintCallable)
	void CharacterHP_Down(int32 DownValue);

	UFUNCTION(BlueprintCallable)
	void CharacterMP_Up(int32 UpValue);
	UFUNCTION(BlueprintCallable)
	void CharacterMP_Down(int32 DownValue);

	UFUNCTION(BlueprintCallable)
	void CharacterSP_Up(int32 UpValue);
	UFUNCTION(BlueprintCallable)
	void CharacterSP_Down(int32 DownValue);

	UFUNCTION(BlueprintCallable)
	FCharacterStat GetCharacterStatus() { return CharacterStatus; };

	UFUNCTION()
	void PrintLog();
};

