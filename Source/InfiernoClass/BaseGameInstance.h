// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Default	UMETA(DisplayName = "Default"),
	Monkey	UMETA(DisplayName = "Monkey"),
	Bull	UMETA(DisplayName = "Bull")
};

UCLASS()
class INFIERNOCLASS_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player References")
	ECharacterClass characterClass;
};