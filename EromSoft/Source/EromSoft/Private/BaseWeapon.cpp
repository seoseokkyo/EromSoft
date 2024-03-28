// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include "CollisionComponent.h"
#include "CombatComponent.h"
#include "Combat_Interface.h"
#include "AnimInstance_Interface.h"

ABaseWeapon::ABaseWeapon()
{
	collisionComponent = CreateDefaultSubobject<UCollisionComponent>(TEXT("CollisionComponent"));
	ItemStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	// 아예 안됨(Dynamic)
	//collisionComponent->onHitDeligate.AddDynamic(this, &ABaseWeapon::OnHitCollisionComponent);

	// UFUNCTION(BlueprintCallable)속성일 때 안됨 UFUNCTION()도 안됨
	//collisionComponent->onHitDeligate.BindUFunction(this, "OnHitCollisionComponent");
	
	// UFUNCTION(BlueprintCallable)속성일 때 안됨 UFUNCTION()도 안됨
	//collisionComponent->onHitDeligate.BindDynamic(this, &ABaseWeapon::OnHitCollisionComponent);
	//collisionComponent->onHitDeligate.__Internal_BindDynamic(this, &ABaseWeapon::OnHitCollisionComponent, TEXT("OnHitCollisionComponent"));
	//collisionComponent->onHitDeligate.BindDynamic(this, &ABaseWeapon::OnHitCollisionComponent);

	// 
	
	if (collisionComponent != nullptr)
	{
		collisionComponent->onHitDeligate.BindUObject(this, &ABaseWeapon::OnHitCollisionComponent);
	}
	else
	{
		int iTemp = 0;
	}
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::OnEquipped()
{
	//Super::OnEquipped();
	if (GetOwner() != nullptr)
	{
		combatComponent = GetOwner()->GetComponentByClass<UCombatComponent>();
		if (combatComponent != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("handSocketName : %s"), *handSocketName.ToString());
			UE_LOG(LogTemp, Warning, TEXT("AttachSocketName : %s"), *AttachSocketName.ToString());

			FName selectedName = (combatComponent->bCombatEnable ? handSocketName : AttachSocketName);

			UE_LOG(LogTemp, Warning, TEXT("CombatComponent.bCombatEnable : %d"), combatComponent->bCombatEnable);
			UE_LOG(LogTemp, Warning, TEXT("selectedName : %s"), *selectedName.ToString());

			AttachActor(selectedName);

			combatComponent->SetMainWeapon(this);

			//Cast<IAnimInstance_Interface>(Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance())->UpdateCombatType(eWeaponType);
						
			ACharacter* characterPtr = Cast<ACharacter>(GetOwner());
			if (characterPtr)
			{
				USkeletalMeshComponent* skeletalMeshComponent = characterPtr->GetMesh();
				if (skeletalMeshComponent)
				{
					UClass* animInstance = skeletalMeshComponent->GetAnimClass();
					
					bool bInterfaceCheck = animInstance->ImplementsInterface(UAnimInstance_Interface::StaticClass());
					
					if (bInterfaceCheck)
					{
						IAnimInstance_Interface::Execute_UpdateCombatType(animInstance, eWeaponType);
					
						UE_LOG(LogTemp, Warning, TEXT("%s Send UpdateCombatType"), *animInstance->GetName());
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("%s Is do not Have IAnimInstance_Interface"), *skeletalMeshComponent->GetName());
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("skeletalMeshComponent Is Nullptr"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Owner Is Not Character"));
			}

			collisionComponent->SetCollisionMesh(GetItemMesh());
			collisionComponent->AddActorToIgnore(GetOwner());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("selectedName : %p"), this);
	}
}

void ABaseWeapon::OnHitCollisionComponent(FHitResult lastHitStruct)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHitCollisionComponent Called"));

	AActor* hitActor = lastHitStruct.GetActor();

	if (Cast<ICombat_Interface>(hitActor)->CanReceiveDamage())
	{
		/*
			 AActor* DamagedActor, 
			 float BaseDamage, 
			 FVector const& HitFromDirection, 
			 FHitResult const& HitInfo, 
			 AController* EventInstigator, 
			 AActor* DamageCauser, 
			 TSubclassOf<UDamageType> DamageTypeClass
		*/

		FVector hitFromDirection = GetOwner()->GetActorForwardVector();
		TSubclassOf<UDamageType> damageTypeClass = {};

		//<< 이거 damageTypeClass랑 블루프린트의 기본값이랑 차이가 있는지 확인필요
		UGameplayStatics::ApplyPointDamage(hitActor, weaponDamage, hitFromDirection, lastHitStruct, GetInstigatorController(), this, damageTypeClass);
	}
}

void ABaseWeapon::SimulateWeaponPhysics()
{
	GetItemMesh()->SetCollisionProfileName(FName("PhysicsActor"));
	GetItemMesh()->SetSimulatePhysics(true);
}
