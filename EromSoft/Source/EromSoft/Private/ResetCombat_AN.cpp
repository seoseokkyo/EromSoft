// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetCombat_AN.h"
#include "Combat_Interface.h"
#include "TarnishedCharacter.h"

void UResetCombat_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp != nullptr)
	{
		auto charCheck = Cast<ATarnishedCharacter>(MeshComp->GetOwner());

		if (charCheck != nullptr)
		{
			if (Cast<ICombat_Interface>(MeshComp->GetOwner()))
			{
				ICombat_Interface::Execute_ResetCombat(charCheck);
				UE_LOG(LogTemp, Warning, TEXT("UResetCombat_AN::Notify - Called"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UResetCombat_AN::Notify - NullptrErr"));
			}
		}
	}
}
