
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPMainMenuWidget.generated.h"

class UButton;
class IPPMenuInterface;
class UWidgetSwitcher;
class UEditableTextBox;

UCLASS()
class PUZZLEPLATFORMS_API UPPMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;
    void SetMenuInterface(IPPMenuInterface* PtrToMenuInterface);

    void Setup();
    void Teardown();
	
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
    UWidgetSwitcher* MenuSwitcher;

    UPROPERTY(meta = (BindWidget))
    UEditableTextBox* AddressTextBox;

    UPROPERTY()
    APlayerController* ClientPlayerController;
    
    IPPMenuInterface* MenuInterface;

    UFUNCTION()
    void OnHostButtonClicked();

    UFUNCTION()
    void OnOpenJoinMenu();

    UFUNCTION()
    void OnOpenMainMenu();

    UFUNCTION()
    void OnConnectButtonClicked();

    bool FindPlayerController();
};
