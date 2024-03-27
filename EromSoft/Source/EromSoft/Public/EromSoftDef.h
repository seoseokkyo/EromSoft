#pragma once

enum class ECharacterStatusType
{
	HP,
	MP,
	SP,
	ECharacterStatusTypeMax
};

DECLARE_DELEGATE_OneParam(FOnHitDeligate, FHitResult);
