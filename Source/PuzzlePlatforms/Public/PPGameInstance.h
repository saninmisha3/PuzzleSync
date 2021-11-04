
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/PPMenuInterface.h"
#include "PPGameInstance.generated.h"

class UPPMainMenuWidget;

UCLASS()
class PUZZLEPLATFORMS_API UPPGameInstance : public UGameInstance, public IPPMenuInterface
{
	GENERATED_BODY()

public:
    UPPGameInstance();

protected:
    UPROPERTY()
    TSubclassOf<UUserWidget> MenuClass;

    UPROPERTY()
    UPPMainMenuWidget* MenuWidget;

    UFUNCTION(BlueprintCallable, Exec)
    void LoadMenu();
    
    UFUNCTION(Exec)
    void Host();

    UFUNCTION(Exec)
    void Join (const FString& Address) ;
};
