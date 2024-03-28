// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachWeaponActor_AN.h"
#include "Combat_Interface.h"
#include "CombatComponent.h"
#include "BaseWeapon.h"

void UAttachWeaponActor_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto checkValid = MeshComp->GetOwner();
	if (checkValid != nullptr)
	{
		TSubclassOf<UCombatComponent> combatCompClass;
		UCombatComponent* combatComp = Cast<UCombatComponent>(checkValid->GetComponentByClass(combatCompClass));

		if (combatComp != nullptr)
		{
			FName attachSocketName("AttachSocketName");
			combatComp->GetMainWeapon()->AttachActor(attachSocketName);
		}
	}
}
