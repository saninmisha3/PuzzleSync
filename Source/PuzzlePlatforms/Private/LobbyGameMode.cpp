

#include "LobbyGameMode.h"

#include "GameMapsSettings.h"
#include "PPGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    
    if(++CountPlayers == 2 && GetWorld())
    {
        bUseSeamlessTravel = true;

        const auto GI = GetGameInstance<UPPGameInstance>();
        if(!GI) return;

        GI->StartSession();
        GetWorld()->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonExampleMap?listen");
    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    --CountPlayers;
}
