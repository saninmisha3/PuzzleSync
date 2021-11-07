
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/PPMenuInterface.h"
#include "PPGameInstance.generated.h"

class UPPMainMenuWidget;
class UPPPauseWidget;

UCLASS()
class PUZZLEPLATFORMS_API UPPGameInstance : public UGameInstance, public IPPMenuInterface
{
	GENERATED_BODY()

public:
    UPPGameInstance();

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

    UFUNCTION(BlueprintCallable, Exec)
    void LoadMenu();
    
    UFUNCTION(Exec)
    void Host() override;

    UFUNCTION(Exec)
    void Join (const FString& Address) override;

    UFUNCTION(Exec)
    void OpenMainMenu() override;
};
