// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateCharactor_ANS.h"
#include "Combat_Interface.h"
#include "Kismet/KismetMathLibrary.h"

void URotateCharactor_ANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	float interpSpeed = 720.0f;

	FRotator ownerRotator = MeshComp->GetOwner()->GetActorRotation();
	FRotator desireRotator = Cast<ICombat_Interface>(MeshComp->GetOwner())->GetDesireRotation();	

	FRotator interpRotator = UKismetMathLibrary::RInterpTo_Constant(ownerRotator, desireRotator, FrameDeltaTime, interpSpeed);

	MeshComp->GetOwner()->SetActorRotation(interpRotator);
}
