
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPMainMenuWidget.generated.h"

class UButton;
class IPPMenuInterface;

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

    UPROPERTY()
    APlayerController* ClientPlayerController;
    
    IPPMenuInterface* MenuInterface;

    UFUNCTION()
    void OnHostButtonClicked();

    UFUNCTION()
    void OnJoinButtonClicked();

    bool FindPlayerController();
};
