

#include "Meshes/PPPlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "PPMovingPlatform.h"

APPPlatformTrigger::APPPlatformTrigger()
{
    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    SetRootComponent(TriggerVolume);

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComp->SetupAttachment(GetRootComponent());

    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APPPlatformTrigger::OnBeginOverlapHandle);
    TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APPPlatformTrigger::OnEndOverlapHandle);
}

void APPPlatformTrigger::OnBeginOverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(!Platforms.Num()) return;
    for(const auto Platform : Platforms)
    {
        Platform->AddActiveTrigger();
    }
}

void APPPlatformTrigger::OnEndOverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if(!Platforms.Num()) return;
    for(const auto Platform : Platforms)
    {
        Platform->RemoveActiveTrigger();
    }
}

void APPPlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

