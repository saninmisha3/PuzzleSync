
#include "PPGameInstance.h"
#include "PPPauseWidget.h"
#include "PPMainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UPPGameInstance::UPPGameInstance()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MenuWBPObject (TEXT("/Game/PuzzlePlatforms/HUD/WBP_MainMenu"));
    if(!MenuWBPObject.Succeeded()) return;
    MenuClass = MenuWBPObject.Class; // TSubclassOf<UUserWidget> 

    static ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuWBPObject (TEXT("/Game/PuzzlePlatforms/HUD/WBP_PauseMenu"));
    if(!PauseMenuWBPObject.Succeeded()) return;
    PauseMenuClass = PauseMenuWBPObject.Class; // TSubclassOf<UUserWidget>
    
    MainMenuLevelPath = "/Game/PuzzlePlatforms/Maps/MainMenu";
}

void UPPGameInstance::CreatePauseWidget()
{
    if(PauseMenuWidget) return;
    PauseMenuWidget = CreateWidget<UPPPauseWidget>(this, PauseMenuClass);
    if(!PauseMenuWidget) return;

    PauseMenuWidget->SetMenuInterface(this);
    PauseMenuWidget->Teardown();
}

void UPPGameInstance::LoadMenu()
{
    MenuWidget = CreateWidget<UPPMainMenuWidget>(this, MenuClass);
    if(!MenuWidget) return;
    
    MenuWidget->SetMenuInterface(this);
    MenuWidget->Setup();
}

void UPPGameInstance::Host()
{
    if(!MenuWidget) return;
    MenuWidget->Teardown();
    
    if(!GetWorld()) return;
    GetWorld()->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonExampleMap?listen");
    
    GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, TEXT("Server was created."));
}

void UPPGameInstance::Join(const FString& Address)
{
    if(Address.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("IP is not correct!"));
        return;
    }

    if(!MenuWidget) return;
    MenuWidget->Teardown();
    
    const auto ClientPlayerController = GetPrimaryPlayerController();
    if(!ClientPlayerController) return;
    
    ClientPlayerController->ClientTravel(Address, TRAVEL_Absolute);
    
    GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString(TEXT("Joining to server...") + Address));
}

void UPPGameInstance::OpenMainMenu()
{
    const auto ClientPlayerController = GetPrimaryPlayerController();
    if(!ClientPlayerController) return;
    
    ClientPlayerController->ClientTravel(MainMenuLevelPath, TRAVEL_Absolute);
}
