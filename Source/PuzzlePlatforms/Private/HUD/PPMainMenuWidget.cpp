
#include "HUD/PPMainMenuWidget.h"

#include "PPMenuInterface.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UPPMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    HostButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnHostButtonClicked);
    ConnectButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnConnectButtonClicked);
    ExitButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnExitButtonClicked);
    
    JoinButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnOpenJoinMenu);
    BackButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnOpenMainMenu);
    
    FindPlayerController();
}

void UPPMainMenuWidget::OnHostButtonClicked()
{
    if(!MenuInterface) return;
    MenuInterface->Host();
}

void UPPMainMenuWidget::OnOpenJoinMenu()
{
    if(!MenuSwitcher) return;
    MenuSwitcher->SetActiveWidgetIndex(1);
}

void UPPMainMenuWidget::OnOpenMainMenu()
{
    if(!MenuSwitcher) return;
    MenuSwitcher->SetActiveWidgetIndex(0);
}

void UPPMainMenuWidget::OnConnectButtonClicked()
{
    if(!MenuInterface || !AddressTextBox || AddressTextBox->Text.IsEmpty()) return;
    MenuInterface->Join(AddressTextBox->GetText().ToString());
}

void UPPMainMenuWidget::OnExitButtonClicked()
{
    if(!FindPlayerController()) return;
    UKismetSystemLibrary::QuitGame(GetWorld(), ClientPlayerController, EQuitPreference::Quit, true);
}
