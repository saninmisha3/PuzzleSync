
#include "HUD/PPMainMenuWidget.h"

#include "PPMenuInterface.h"
#include "PPServerInstanceWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/VerticalBox.h"
#include "PPServerInstanceWidget.h"

void UPPMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    HostButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnHostButtonClicked);
    CreateServerButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnCreateServerButtonClicked);
    ConnectButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnConnectButtonClicked);
    ExitButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnExitButtonClicked);
    
    JoinButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnOpenJoinMenu);
    BackButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnOpenMainMenu);
    
    FindPlayerController();
}

void UPPMainMenuWidget::AddServerRow(const FString& ServerName, const uint32 ServerIndex, const FString& HostName, const uint32 CurrentPlayers, const uint32 MaxPlayers)
{
    if(!ServerTextBlockClass || !ServerListWrapper) return;
    
    const auto ServerRow = CreateWidget<UPPServerInstanceWidget>(this, ServerTextBlockClass);
    if(!ServerRow) return;

    const FServerData ServerInfo {ServerName,ServerIndex,CurrentPlayers,MaxPlayers,HostName};

    ServerList.Add(ServerInfo);

    ServerRow->SetServerData(&ServerList.Last());
    
    ServerListWrapper->AddChildToVerticalBox(ServerRow);
}

void UPPMainMenuWidget::OnHostButtonClicked()
{
    if(!MenuSwitcher || !MenuInterface) return;
    MenuSwitcher->SetActiveWidgetIndex(2);
}

void UPPMainMenuWidget::OnOpenJoinMenu()
{
    if(!MenuSwitcher || !MenuInterface) return;
    MenuSwitcher->SetActiveWidgetIndex(1);
    MenuInterface->SearchServers();
}

void UPPMainMenuWidget::OnOpenMainMenu()
{
    if(!MenuSwitcher) return;
    MenuSwitcher->SetActiveWidgetIndex(0);
}

void UPPMainMenuWidget::OnConnectButtonClicked()
{
    if(!MenuInterface || !AddressTextBox) return;
    
    if(!AddressTextBox->Text.IsEmpty())
    {
        MenuInterface->Join(AddressTextBox->GetText().ToString());
        return;
    }

    MenuInterface->SearchServers();
}

void UPPMainMenuWidget::OnExitButtonClicked()
{
    if(!FindPlayerController()) return;
    UKismetSystemLibrary::QuitGame(GetWorld(), ClientPlayerController, EQuitPreference::Quit, true);
}

void UPPMainMenuWidget::OnCreateServerButtonClicked()
{
    MenuInterface->Host(HostServerName->GetText().ToString());
}
