
#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PPMovingPlatform.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API APPMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
    APPMovingPlatform();
    
    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
    float Speed;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta = (MakeEditWidget = true))
    FVector TargetPoint;

    FVector UnitMovementDirection;
    FVector StartLocation;
    FVector TargetLocation;
};
