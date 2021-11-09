
#pragma once

#include "CoreMinimal.h"
#include "PPMenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PPServerInstanceWidget.generated.h"

class UButton;
class IPPMenuInterface;
UCLASS()
class PUZZLEPLATFORMS_API UPPServerInstanceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    TOptional<uint32> ServerIndex;

    virtual void NativeOnInitialized() override;
    
    FORCEINLINE void SetServerText(const FText& Text) const {ServerName->SetText(Text);}
    FORCEINLINE void SetServerIndex(const uint32& Index) {ServerIndex = Index;}
    
protected:    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* ServerName;

    UPROPERTY(meta = (BindWidget))
    UButton* ServerButton;

    UFUNCTION()
    void OnServerButtonClicked();

};
