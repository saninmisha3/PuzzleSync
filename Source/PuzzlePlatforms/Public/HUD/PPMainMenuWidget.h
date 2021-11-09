
#pragma once

#include <PPBaseWidget.h>

#include "Components/VerticalBox.h"
#include "PPMainMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UEditableTextBox;
class UVerticalBox;
class UPPServerInstanceWidget;

UCLASS()
class PUZZLEPLATFORMS_API UPPMainMenuWidget : public UPPBaseWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    void AddServerRow(const FString& ServerName, const uint32 ServerIndex);
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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
    TSubclassOf<UPPServerInstanceWidget> ServerTextBlockClass;

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
