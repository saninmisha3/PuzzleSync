
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
    SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPPGameInstance::OnFindSessionsHandle);
    SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPPGameInstance::OnJoinSessionHandle);
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

void UPPGameInstance::Host(const FString& ServerName)
{
    if(!SessionInterface) return;

    const auto SessionName = SessionInterface->GetNamedSession(GSession_Name);
    
    if(SessionName)
        SessionInterface->DestroySession(GSession_Name);
    
    CreateSession(ServerName);
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

void UPPGameInstance::SearchServers()
{
    SessionSearchPtr = MakeShareable(new FOnlineSessionSearch());
    if(!SessionSearchPtr) return;
    SessionSearchPtr->bIsLanQuery = false; // Search in Local Network
    SessionSearchPtr->MaxSearchResults = 10; // Count of Lobbies for Search Result 
    SessionSearchPtr->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); // Find Steam Lobbies
    
    SessionInterface->FindSessions(0, SessionSearchPtr.ToSharedRef());
}

void UPPGameInstance::SetServerIndex(const uint32& Index)
{
    ServerIndex = Index;
    
    if(!ServerIndex.IsSet()) return;
    UE_LOG(LogSessionInfo, Display, TEXT("Connecting to Server %i"), ServerIndex.GetValue());
    
    const auto FindSessionResults = SessionSearchPtr->SearchResults;
    if(!FindSessionResults.Num()) return;
    
    SessionInterface->JoinSession(0,GSession_Name,FindSessionResults[ServerIndex.GetValue()]);
}

void UPPGameInstance::CreateSession(const FString& ServerName)
{
    if(!SessionInterface) return;
    FOnlineSessionSettings SessionSettings;
    if(IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
        SessionSettings.bIsLANMatch = true; // Local
    else
        SessionSettings.bIsLANMatch = false; // Network

    SessionSettings.NumPublicConnections = 2; // Player number
    SessionSettings.bShouldAdvertise = true; // Can find by search
    SessionSettings.bUsesPresence = true; // true = SteamLobby, false = SteamInternet
    SessionSettings.Set(TEXT("ServerName"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    
    if(SessionInterface->CreateSession(0, GSession_Name, SessionSettings))
        UE_LOG(LogSessionInfo, Display, TEXT("New %s successfully created."), *GSession_Name.ToString());
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
}

void UPPGameInstance::OnFindSessionsHandle(const bool IsSuccess)
{
    if(!IsSuccess || !SessionSearchPtr || !MenuWidget) return;
    UE_LOG(LogSessionInfo, Display, TEXT("Find Sessions is Success"));

    const auto FindSessionResults = SessionSearchPtr->SearchResults;
    if(!FindSessionResults.Num()) return;

    MenuWidget->ClearServerList();
    uint32 IteratorIndex = 0;
    for(const auto& SessionResult : FindSessionResults)
    {
        if(!SessionResult.IsValid()) continue;

        FString ServerName;
        SessionResult.Session.SessionSettings.Get(TEXT("ServerName"), ServerName);
        const auto HostName = SessionResult.Session.OwningUserName;
        const auto MaxPlayers = SessionResult.Session.SessionSettings.NumPublicConnections;
        const auto CurrentPlayers = MaxPlayers - SessionResult.Session.NumOpenPublicConnections;
        
        MenuWidget->AddServerRow(ServerName, IteratorIndex++, HostName, CurrentPlayers, MaxPlayers);
        UE_LOG(LogSessionInfo, Display, TEXT("Found server - %s"), *SessionResult.GetSessionIdStr());
    }
}

void UPPGameInstance::OnJoinSessionHandle(const FName SessionName, const EOnJoinSessionCompleteResult::Type ResultType)
{
    if(ResultType != EOnJoinSessionCompleteResult::Success) return;

    FString TravelURL;
    if(SessionInterface->GetResolvedConnectString(SessionName,TravelURL))
        Join(TravelURL);
}
