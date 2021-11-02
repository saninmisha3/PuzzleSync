
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPPlatformTrigger.generated.h"

class UBoxComponent;
class APPMovingPlatform;

UCLASS()
class PUZZLEPLATFORMS_API APPPlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	APPPlatformTrigger();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UBoxComponent* TriggerVolume;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interactive")
    TArray<APPMovingPlatform*> Platforms;

    UFUNCTION()
    void OnBeginOverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
    UFUNCTION()
    void OnEndOverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
	virtual void BeginPlay() override;
};
