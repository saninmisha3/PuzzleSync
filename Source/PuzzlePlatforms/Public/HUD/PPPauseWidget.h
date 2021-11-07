
#pragma once

#include <PPBaseWidget.h>

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "PPPauseWidget.generated.h"

class UButton;

UCLASS()
class PUZZLEPLATFORMS_API UPPPauseWidget : public UPPBaseWidget
{
	GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ReturnButton;

    UPROPERTY(meta = (BindWidget))
    UButton* MainMenuButton;
    
    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;

    UFUNCTION()
    void OnMainMenuButtonClicked();

    UFUNCTION()
    void OnExitButtonClicked();
};
