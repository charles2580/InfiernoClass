// Copyright Epic Games, Inc. All Rights Reserved.
#include "InfiernoClassGameModeBase.h"
#include "BaseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AInfiernoClassGameModeBase::AInfiernoClassGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnBPClass(TEXT("/Game/Models/Characters/TestMonkey"));
	if (DefaultPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = DefaultPawnBPClass.Class;
	}
}

void AInfiernoClassGameModeBase::StartPlay()
{
    Super::StartPlay();

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // --- 1. GameInstance���� ���õ� ĳ���� Ŭ������ �о�� ---
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetGameInstance());
    if (!GI)
    {
        UE_LOG(LogTemp, Log, TEXT("GameInstance casting Fail"));
        return;
    }

    TSubclassOf<ABaseCharacter> SelectedPawnClass = nullptr;
    if (GI->characterClass == ECharacterClass::Monkey)
    {
        SelectedPawnClass = MonkeyPawnClass;
        UE_LOG(LogTemp, Log, TEXT("Selected Character Class: Monkey"));
    }
    else if (GI->characterClass == ECharacterClass::Bull)
    {
        SelectedPawnClass = BullPawnClass;
        UE_LOG(LogTemp, Log, TEXT("Selected Character Class: Bull"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Non Defined Character"));
        return;
    }

    if (!SelectedPawnClass)
    {
        UE_LOG(LogTemp, Log, TEXT("There is No SelectedCharacterClass"));
        return;
    }

    // --- 2. Player 0 ���� �� Pawn ����/Possess ---
    APlayerController* PC0 = World->GetFirstPlayerController();
    if (PC0)
    {
        FVector SpawnLocation0(-200.f, 0.f, 100.f); // ���ϴ� ��ġ�� ����
        FRotator SpawnRotation0 = FRotator::ZeroRotator;
        FTransform SpawnTransform0(SpawnRotation0, SpawnLocation0, FVector(1.0f));

        ABaseCharacter* Pawn0 = World->SpawnActorDeferred<ABaseCharacter>(SelectedPawnClass, SpawnTransform0);
        if (Pawn0)
        {
            Pawn0->AutoPossessPlayer = EAutoReceiveInput::Player0;
            Pawn0->CharacterIndex = 1;
            Pawn0->FinishSpawning(SpawnTransform0);

            Player1 = Pawn0;
            UE_LOG(LogTemp, Log, TEXT("Spawning Player1 Pawn: %s"), *Pawn0->GetName());
            // Possess()�� 0.1�� ���� �� ȣ��
            FTimerHandle TimerHandle0;
            World->GetTimerManager().SetTimer(TimerHandle0, [PC0, Pawn0]()
                {
                    PC0->Possess(Pawn0);
                    UE_LOG(LogTemp, Log, TEXT("Player 0 Pawn Spawn and Possess (Delayed) Success"));
                }, 0.1f, false);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player 0 Pawn Spawn Failed."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player 0 Controller Can't Find."));
    }

    // --- 3. Player 1 (�߰� �÷��̾�) ���� ---
    if (GetNumPlayers() < 2)
    {
        UGameInstance* GameInst = GetGameInstance();
        if (GameInst)
        {
            FString PlayerName = FString(TEXT("Player2"));
            ULocalPlayer* NewLocalPlayer = GameInst->CreateLocalPlayer(1, PlayerName, true);
            if (NewLocalPlayer)
            {
                UE_LOG(LogTemp, Log, TEXT("Second Local Player Spawned."));
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Second Local Player Spawn Failed."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("GameInstance does not exist."));
        }
    }

    // --- 4. Player 1�� PlayerController �� Pawn ����/Possess ---
    APlayerController* PC1 = nullptr;
    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (PC && PC != World->GetFirstPlayerController())
        {
            PC1 = PC;
            break;
        }
    }

    if (PC1)
    {
        FVector SpawnLocation1(200.f, 0.f, 100.f); // �� ��° Pawn�� ��ġ
        FRotator SpawnRotation1(0.0f, 180.0f, 0.0f);
        FTransform SpawnTransform1(SpawnRotation1, SpawnLocation1, FVector(1.0f));

        ABaseCharacter* Pawn1 = World->SpawnActorDeferred<ABaseCharacter>(BullPawnClass, SpawnTransform1);
        if (Pawn1)
        {
            Pawn1->AutoPossessPlayer = EAutoReceiveInput::Player1;
            USkeletalMeshComponent* MeshComp = Pawn1->GetMesh();
            FVector NewScale = MeshComp->GetRelativeScale3D();
            NewScale.Y *= -1.f;
            MeshComp->SetRelativeScale3D(NewScale);
            Pawn1->CharacterIndex = 2;
            Pawn1->FinishSpawning(SpawnTransform1);

            Player2 = Pawn1;
            UE_LOG(LogTemp, Log, TEXT("Spawning Player2 Pawn: %s"), *Pawn1->GetName());
            // Possess()�� 0.1�� ���� �� ȣ��
            FTimerHandle TimerHandle1;
            World->GetTimerManager().SetTimer(TimerHandle1, [PC1, Pawn1]()
                {
                    PC1->Possess(Pawn1);
                    // �ʿ�� �Է� ��嵵 �缳��
                    FInputModeGameAndUI InputMode;
                    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                    PC1->SetInputMode(InputMode);
                    UE_LOG(LogTemp, Log, TEXT("Player 1 Pawn Spawn and Possess (Delayed) Success"));
                }, 0.1f, false);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player 1 Pawn Spawn Failed."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player 1 Controller does not Possess."));
    }
}

void AInfiernoClassGameModeBase::OnCharacterDead(ABaseCharacter* DeadCharacter)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetGameInstance());

    if (!GI)
    {
        return;
    }

    if (DeadCharacter == Player1)
    {
        GI->Player2WinCount++;
        Player2->PlayerWin();
        // HUD�� "Player 2 Wins!" ǥ�� ��
    }
    else if (DeadCharacter == Player2)
    {
        GI->Player1WinCount++;
        Player1->PlayerWin();
        // HUD�� "Player 1 Wins!" ǥ�� ��
    }

    GI->GameRound++;

    const int32 WinLimit = 3;
    if (GI->Player1WinCount >= WinLimit || GI->Player2WinCount >= WinLimit)
    {
        // ���� �¸� ó�� (UI ǥ�� �� �޴��� ��ȯ ��)
        /*UE_LOG(LogTemp, Warning, TEXT("Final Winner: %s"),
            (GI->Player1WinCount >= WinLimit ? TEXT("Player 1") : TEXT("Player 2")));*/
        GI->Player1WinCount = 0;
        GI->Player2WinCount = 0;
        GI->GameRound = 0;
        FTimerHandle RestartHandle;
        InitializeWinUI();
        GetWorld()->GetTimerManager().SetTimer(RestartHandle, [this]()
            {
                UGameplayStatics::OpenLevel(this, "Level1");
            }, 5.0f, false);
    }

    else
    {
        // ���� ���� ������ ���� ���� �����
        FTimerHandle RestartHandle;
        GetWorld()->GetTimerManager().SetTimer(RestartHandle, [this]()
            {
                UGameplayStatics::OpenLevel(this, "PGY");
            }, 3.0f, false);
    }
}
