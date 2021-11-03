
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PPGameInstance.generated.h"


UCLASS()
class PUZZLEPLATFORMS_API UPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    UPPGameInstance();

protected:
    UPROPERTY()
    TSubclassOf<UUserWidget> MenuClass;
    
    UFUNCTION(Exec)
    void Host();

    UFUNCTION(Exec)
    void Join (const FString& Address);
};
