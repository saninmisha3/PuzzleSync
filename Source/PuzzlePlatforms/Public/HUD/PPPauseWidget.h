
#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "PPPauseWidget.generated.h"

class UButton;

UCLASS()
class PUZZLEPLATFORMS_API UPPPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ReturnButton;

    UPROPERTY(meta = (BindWidget))
    UButton* MainMenuButton;
    
    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;
};
