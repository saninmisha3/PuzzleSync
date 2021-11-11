
#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatforms/PuzzlePlatformsGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ALobbyGameMode : public APuzzlePlatformsGameMode
{
	GENERATED_BODY()

public:
    
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;

protected:
    uint32 CountPlayers = 0;
};
