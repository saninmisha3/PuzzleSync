
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/PPMenuInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PPGameInstance.generated.h"

class UPPMainMenuWidget;
class UPPPauseWidget;

UCLASS()
class PUZZLEPLATFORMS_API UPPGameInstance : public UGameInstance, public IPPMenuInterface
{
	GENERATED_BODY()

public:
    UPPGameInstance();

    virtual void Init() override;

    UFUNCTION(BlueprintCallable, Category="Widgets")
    void CreatePauseWidget();

    UFUNCTION(BlueprintPure, Category="Widgets")
    FORCEINLINE UPPPauseWidget* GetPauseMenu() const {return PauseMenuWidget;}

protected:
    UPROPERTY()
    TSubclassOf<UPPMainMenuWidget> MenuClass;

    UPROPERTY()
    UPPMainMenuWidget* MenuWidget;
    
    UPROPERTY()
    TSubclassOf<UPPPauseWidget> PauseMenuClass;

    UPROPERTY()
    UPPPauseWidget* PauseMenuWidget;

    UPROPERTY(EditDefaultsOnly, Category="Levels")
    FString MainMenuLevelPath;

    IOnlineSessionPtr SessionInterface;

    UFUNCTION(BlueprintCallable, Exec)
    void LoadMenuWidget();
    
    UFUNCTION(Exec)
    void Host() override;

    UFUNCTION(Exec)
    void Join (const FString& Address) override;

    UFUNCTION(Exec)
    void OpenMainMenu() override;

    void OnCreateSessionHandle(const FName SessionName, const bool IsSuccess);
    void OnDestroySessionHandle(const FName SessionName, const bool IsSuccess);

    void CreateSession();
    
};
