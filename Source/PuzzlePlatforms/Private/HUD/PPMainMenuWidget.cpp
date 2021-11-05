
#include "HUD/PPMainMenuWidget.h"
#include "Components/Button.h"
#include "Interfaces/PPMenuInterface.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

void UPPMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    HostButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnHostButtonClicked);
    ConnectButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnConnectButtonClicked);
    
    JoinButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnOpenJoinMenu);
    BackButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnOpenMainMenu);
    
    FindPlayerController();
}

void UPPMainMenuWidget::Setup()
{
    SetVisibility(ESlateVisibility::Visible);
    bIsFocusable = 1;
    AddToViewport();

    if(!FindPlayerController()) return;

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(TakeWidget()); // Need add bIsFocusable to Widget
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
    
    ClientPlayerController->SetInputMode(InputMode);
    //ClientPlayerController->SetInputMode(FInputModeUIOnly()); Simple Alternative Method
    
    ClientPlayerController->bShowMouseCursor = true;
}

void UPPMainMenuWidget::Teardown()
{
    SetVisibility(ESlateVisibility::Hidden);
    bIsFocusable = 0;
    
    if(!FindPlayerController()) return;
    ClientPlayerController->SetInputMode(FInputModeGameOnly());
    ClientPlayerController->bShowMouseCursor = false;
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

bool UPPMainMenuWidget::FindPlayerController()
{
    if(ClientPlayerController) return true;
    if(!GetWorld()) return false;
    ClientPlayerController = GetWorld()->GetFirstPlayerController();
    return ClientPlayerController ? true : false;
}

void UPPMainMenuWidget::SetMenuInterface(IPPMenuInterface* PtrToMenuInterface)
{
    MenuInterface = PtrToMenuInterface;
}