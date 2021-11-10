
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

    void SetServerIndex(const uint32& Index);

protected:
    TOptional<uint32> ServerIndex;
    
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


    TSharedPtr<FOnlineSessionSearch> SessionSearchPtr;

    UFUNCTION(BlueprintCallable, Exec)
    void LoadMenuWidget();
    
    UFUNCTION(Exec)
    virtual void Host(const FString& ServerName) override;

    UFUNCTION(Exec)
    virtual void Join (const FString& Address) override;

    UFUNCTION(Exec)
    virtual void OpenMainMenu() override;

    UFUNCTION(Exec)
    virtual void SearchServers() override;

    void OnCreateSessionHandle(const FName SessionName, const bool IsSuccess);
    void OnDestroySessionHandle(const FName SessionName, const bool IsSuccess);
    void OnFindSessionsHandle(const bool IsSuccess);
    void OnJoinSessionHandle(const FName SessionName, const EOnJoinSessionCompleteResult::Type ResultType);

    void CreateSession(const FString& ServerName);
    
};
