
#include "HUD/PPMainMenuWidget.h"
#include "Components/Button.h"
#include "Interfaces/PPMenuInterface.h"

void UPPMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    HostButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnHostButtonClicked);
    JoinButton->OnClicked.AddDynamic(this, &UPPMainMenuWidget::OnJoinButtonClicked);
    
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

void UPPMainMenuWidget::OnJoinButtonClicked()
{
    
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