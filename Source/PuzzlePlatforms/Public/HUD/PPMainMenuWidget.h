
#pragma once

#include <PPBaseWidget.h>
#include "PPMainMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UEditableTextBox;

UCLASS()
class PUZZLEPLATFORMS_API UPPMainMenuWidget : public UPPBaseWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

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
};
