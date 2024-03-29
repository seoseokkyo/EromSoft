// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEquippable.h"
#include "AnimInstance_Interface.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
class UCollisionComponent;
class UCombatComponent;
/*
* 블루프린트에서 호출되고 있는 ABaseEquippable기능들 중 분석해봐야 되는 내용
* BeginPlay
* ActorBeginOverlap
* Event Tick
* Construction Script (생성자)
*/

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	None = 0				UMETA(DisplayName = "None"),
	LightSword				UMETA(DisplayName = "LightSword"),
	GreatSword				UMETA(DisplayName = "GreatSword"),
	E_WeaponTypeMax
};

UCLASS()
class EROMSOFT_API ABaseWeapon : public ABaseEquippable, public IAnimInstance_Interface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	//<< 이거 블루프린트에서 부르고 있는 이유 잘 모르겠음 번역 끝나고 한번 보자
	virtual void BeginPlay() override;

public:
	//<< 이거 블루프린트에서 부르고 있는 이유 잘 모르겠음 번역 끝나고 한번 보자
	virtual void Tick(float DeltaTime) override;


public:

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization")
	FName handSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization")
	E_WeaponType			eWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage*			enterCombatMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage*			exitCombatMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TArray<UAnimMontage*>	attackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TArray<UAnimMontage*>	dodgeMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")

	UCollisionComponent* collisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCombatComponent* combatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization")
	float weaponDamage;

	// Functions
	void OnEquipped();

	UFUNCTION()
	void OnHitCollisionComponent(FHitResult lastHitStruct);

	UFUNCTION(BlueprintCallable)
	void SimulateWeaponPhysics();

	virtual void UpdateCombatType_Implementation(E_WeaponType eWeaponType) override;
	virtual void UpdateCombatEnabled_Implementation(bool bEnable) override;
};
