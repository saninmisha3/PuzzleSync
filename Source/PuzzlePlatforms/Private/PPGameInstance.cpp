
#include "PPGameInstance.h"

#include "PPMainMenuWidget.h"
#include "Blueprint/UserWidget.h"

UPPGameInstance::UPPGameInstance()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MenuWBPObject (TEXT("/Game/PuzzlePlatforms/HUD/WBP_MainMenu"));
    if(!MenuWBPObject.Succeeded()) return;
    MenuClass = MenuWBPObject.Class; // TSubclassOf<UUserWidget> MenuClass
    
    if(!MenuClass) return;
    UE_LOG(LogTemp, Display, TEXT("MenuClass - %s"), *MenuClass->GetName());
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
    GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
    
    GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, TEXT("Server was created."));
}

void UPPGameInstance::Join(const FString& Address)
{
    if(Address.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("IP is not correct!"));
        return;
    }

    const auto ClientPlayerController = GetPrimaryPlayerController();
    if(!ClientPlayerController) return;
    
    ClientPlayerController->ClientTravel(Address, TRAVEL_Absolute);
    
    GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString(TEXT("Joining to server...") + Address));
}
