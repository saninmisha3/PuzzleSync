
#include "PPGameInstance.h"
#include "PPPauseWidget.h"
#include "PPMainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

const static FName GSession_Name = "Testing Session";

DEFINE_LOG_CATEGORY_STATIC(LogSessionInfo, All, Log);

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

void UPPGameInstance::Init()
{
    Super::Init();

    const auto OnlineSubsystem = IOnlineSubsystem::Get();
    if(!OnlineSubsystem)
    {
        UE_LOG(LogSessionInfo, Error, TEXT("UPPGameInstance::Init OnlineSubsystem is Not Valid."));
        return;
    }

    UE_LOG(LogSessionInfo, Display, TEXT("UPPGameInstance::Init OnlineSubsystem - %s."), *OnlineSubsystem->GetSubsystemName().ToString());
    
    SessionInterface = OnlineSubsystem->GetSessionInterface();
    if(!SessionInterface.IsValid())
    {
        UE_LOG(LogSessionInfo, Error, TEXT("UPPGameInstance::Init SessionInterface is Not Valid."));
        return;
    }
    SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPPGameInstance::OnCreateSessionHandle);
    SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPPGameInstance::OnDestroySessionHandle);
}

void UPPGameInstance::CreatePauseWidget()
{
    if(PauseMenuWidget) return;
    PauseMenuWidget = CreateWidget<UPPPauseWidget>(this, PauseMenuClass);
    if(!PauseMenuWidget) return;

    PauseMenuWidget->SetMenuInterface(this);
    PauseMenuWidget->Teardown();
}

void UPPGameInstance::LoadMenuWidget()
{
    MenuWidget = CreateWidget<UPPMainMenuWidget>(this, MenuClass);
    if(!MenuWidget) return;
    
    MenuWidget->SetMenuInterface(this);
    MenuWidget->Setup();
}

void UPPGameInstance::Host()
{
    if(!SessionInterface) return;

    const auto SessionName = SessionInterface->GetNamedSession(GSession_Name);
    if(SessionName)
        SessionInterface->DestroySession(GSession_Name);
    else
        CreateSession();
}

void UPPGameInstance::Join(const FString& Address)
{
    if(Address.IsEmpty())
    {
        UE_LOG(LogSessionInfo, Error, TEXT("IP is not correct!"));
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

void UPPGameInstance::OnCreateSessionHandle(const FName SessionName, const bool IsSuccess)
{
    if(!MenuWidget || !IsSuccess) return;
    MenuWidget->Teardown();

    if(!GetWorld()) return;
    GetWorld()->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonExampleMap?listen");
    
    GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, TEXT("Server was created."));
}

void UPPGameInstance::OnDestroySessionHandle(const FName SessionName, const bool IsSuccess)
{
    if(!IsSuccess) return;
    UE_LOG(LogSessionInfo, Display, TEXT("The %s was destroyed. Start creating a new session."), *SessionName.ToString());
    CreateSession();
}

void UPPGameInstance::CreateSession()
{
    if(!SessionInterface) return;
    FOnlineSessionSettings SessionSettings;
    if(SessionInterface->CreateSession(0, GSession_Name, SessionSettings))
        UE_LOG(LogSessionInfo, Display, TEXT("New %s successfully created."), *GSession_Name.ToString());
}
