// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateCharactor_ANS.h"
#include "Combat_Interface.h"
#include "Kismet/KismetMathLibrary.h"

void URotateCharactor_ANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	float interpSpeed = 720.0f;
	FRotator ownerRotator;
	FRotator desireRotator;

	auto ownerCheck = Cast<ICombat_Interface>(MeshComp->GetOwner());

	if (MeshComp->GetOwner() && ownerCheck)
	{
		ownerRotator = MeshComp->GetOwner()->GetActorRotation();
		desireRotator = ownerCheck->GetDesireRotation();

		FRotator interpRotator = UKismetMathLibrary::RInterpTo_Constant(ownerRotator, desireRotator, FrameDeltaTime, interpSpeed);

		MeshComp->GetOwner()->SetActorRotation(interpRotator);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("URotateCharactor_ANS::NotifyTick - NullptrErr"));
	}
}
