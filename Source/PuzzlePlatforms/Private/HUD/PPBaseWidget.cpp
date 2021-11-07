

#include "HUD/PPBaseWidget.h"

void UPPBaseWidget::Setup()
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

void UPPBaseWidget::Teardown()
{
    SetVisibility(ESlateVisibility::Hidden);
    bIsFocusable = 0;
    
    if(!FindPlayerController()) return;
    ClientPlayerController->SetInputMode(FInputModeGameOnly());
    ClientPlayerController->bShowMouseCursor = false;
}

bool UPPBaseWidget::FindPlayerController()
{
    if(ClientPlayerController) return true;
    if(!GetWorld()) return false;
    ClientPlayerController = GetWorld()->GetFirstPlayerController();
    return ClientPlayerController ? true : false;
}

void UPPBaseWidget::SetMenuInterface(IPPMenuInterface* PtrToMenuInterface)
{
    MenuInterface = PtrToMenuInterface;
}