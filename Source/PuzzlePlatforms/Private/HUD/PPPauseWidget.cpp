

#include "HUD/PPPauseWidget.h"
#include "Interfaces/PPMenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UPPPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    ReturnButton->OnClicked.AddDynamic(this, &UPPPauseWidget::Teardown);
    MainMenuButton->OnClicked.AddDynamic(this, &UPPPauseWidget::OnMainMenuButtonClicked);
    ExitButton->OnClicked.AddDynamic(this, &UPPPauseWidget::OnExitButtonClicked);
    
    FindPlayerController();
}
void UPPPauseWidget::OnMainMenuButtonClicked()
{
    if(!MenuInterface) return;
    MenuInterface->OpenMainMenu();
}

void UPPPauseWidget::OnExitButtonClicked()
{
    if(!FindPlayerController()) return;
    UKismetSystemLibrary::QuitGame(GetWorld(), ClientPlayerController, EQuitPreference::Quit, true);
}
