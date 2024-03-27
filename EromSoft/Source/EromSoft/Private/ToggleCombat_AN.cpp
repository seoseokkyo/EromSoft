// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleCombat_AN.h"
#include "Combat_Interface.h"
#include "CombatComponent.h"
#include "BaseWeapon.h"

void UToggleCombat_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	TSubclassOf<UCombatComponent> combatCompClass;

	UCombatComponent* combatComp = Cast<UCombatComponent>(MeshComp->GetOwner()->GetComponentByClass(combatCompClass));

	if (combatComp != nullptr)
	{
		ABaseWeapon* mainWeapon = combatComp->GetMainWeapon();

		if (IsValid(mainWeapon))
		{
			FName selectName = (bEnableCombat ? mainWeapon->handSocketName : mainWeapon->AttachSocketName);

			mainWeapon->AttachActor(selectName);

			combatComp->SetCombatEnabled(bEnableCombat);
		}
	}
}
