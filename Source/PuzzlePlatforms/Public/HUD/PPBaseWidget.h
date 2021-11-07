
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPBaseWidget.generated.h"


class IPPMenuInterface;

UCLASS()
class PUZZLEPLATFORMS_API UPPBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    virtual void Setup();

    UFUNCTION(BlueprintCallable)
    virtual void Teardown();
    
    void SetMenuInterface(IPPMenuInterface* PtrToMenuInterface);

protected:
    UPROPERTY()
    APlayerController* ClientPlayerController;
    
    IPPMenuInterface* MenuInterface;
    
    bool FindPlayerController();
};
