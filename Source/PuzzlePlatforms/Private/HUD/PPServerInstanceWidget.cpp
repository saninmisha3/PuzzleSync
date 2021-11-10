

#include "HUD/PPServerInstanceWidget.h"

#include "PPGameInstance.h"
#include "PPMainMenuWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PPMenuInterface.h"

void UPPServerInstanceWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if(ServerButton)
        ServerButton->OnClicked.AddDynamic(this, &UPPServerInstanceWidget::OnServerButtonClicked);
}

void UPPServerInstanceWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if(!ServerData) return;

    ServerName->SetText(FText::FromString(ServerData->ServerName));
    CurrentPlayers->SetText(FText::AsNumber(ServerData->CurrentPlayers));
    MaxPlayers->SetText(FText::AsNumber(ServerData->MaxPlayers));
}

void UPPServerInstanceWidget::OnServerButtonClicked()
{
    const auto GI = GetGameInstance<UPPGameInstance>();
    if(!GI) return;
    GI->SetServerIndex(ServerData->ServerIndex);
}
