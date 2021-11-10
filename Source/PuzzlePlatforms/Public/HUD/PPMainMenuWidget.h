
#pragma once

#include <PPBaseWidget.h>

#include "Components/VerticalBox.h"
#include "PPMainMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UEditableTextBox;
class UVerticalBox;
class UPPServerInstanceWidget;

USTRUCT()
struct FServerData
{
    GENERATED_BODY()

    FString ServerName;
    uint32 ServerIndex;
    uint32 CurrentPlayers;
    uint32 MaxPlayers;
    FString HostPlayerName;
};

UCLASS()
class PUZZLEPLATFORMS_API UPPMainMenuWidget : public UPPBaseWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    void AddServerRow(const FString& ServerName, const uint32 ServerIndex, const FString& HostName, const uint32 CurrentPlayers, const uint32 MaxPlayers);
    FORCEINLINE void ClearServerList() const {ServerListWrapper->ClearChildren();}
    
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* HostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* JoinButton;
    
    UPROPERTY(meta = (BindWidget))
    UButton* ConnectButton;

    UPROPERTY(meta = (BindWidget))
    UButton* BackButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* MenuSwitcher;

    UPROPERTY(meta = (BindWidget))
    UEditableTextBox* AddressTextBox;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* ServerListWrapper;

    UPROPERTY(meta = (BindWidget))
    UEditableTextBox* HostServerName;

    UPROPERTY(meta = (BindWidget))
    UButton* CreateServerButton;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
    TSubclassOf<UPPServerInstanceWidget> ServerTextBlockClass;

    TArray<FServerData> ServerList;

    UFUNCTION()
    void OnHostButtonClicked();

    UFUNCTION()
    void OnOpenJoinMenu();

    UFUNCTION()
    void OnOpenMainMenu();

    UFUNCTION()
    void OnConnectButtonClicked();

    UFUNCTION()
    void OnExitButtonClicked();

    UFUNCTION()
    void OnCreateServerButtonClicked();
};
