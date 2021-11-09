

#include "HUD/PPServerInstanceWidget.h"

#include "PPGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PPMenuInterface.h"


void UPPServerInstanceWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if(ServerButton)
        ServerButton->OnClicked.AddDynamic(this, &UPPServerInstanceWidget::OnServerButtonClicked);
}

void UPPServerInstanceWidget::OnServerButtonClicked()
{
    if(!ServerIndex.IsSet()) return;
    
    const auto GI = GetGameInstance<UPPGameInstance>();
    if(!GI) return;
    
    GI->SetServerIndex(ServerIndex.GetValue());
}