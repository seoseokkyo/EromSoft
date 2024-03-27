// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTrace_ANs.h"
#include "CombatComponent.h"
#include "BaseWeapon.h"
#include "CollisionComponent.h"

void UCollisionTrace_ANs::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	TSubclassOf<UCombatComponent> combatComp;
	ABaseWeapon* mainWeapon = Cast<UCombatComponent>(MeshComp->GetOwner()->GetComponentByClass(combatComp))->GetMainWeapon();
	if (combatComp != nullptr && mainWeapon != nullptr)
	{
		mainWeapon->collisionComponent->SetEnableCollision(false);
	}
}
