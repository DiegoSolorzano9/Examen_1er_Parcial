// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PVZ_USFX_LAB02GameMode.generated.h"

class AZombie;
class APlant;
class APotenciador;

UCLASS(MinimalAPI)
class APVZ_USFX_LAB02GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    APVZ_USFX_LAB02GameMode();

    TMap<FString, APlant*> MapPlants; // TMap para plantas
    TMap<FString, TMap<FString, AZombie*>> MapZombieGroups; // TMap para grupos de zombies
    TMap<FString, uint32> MapPotenciadores;
    TMap<FString, uint32> MapTarjetasPlantas;

    int32 NumberZombiesPerGroup = 5; // Cantidad de zombies por grupo
    float ZombieGroupSpawnInterval = 5.0f; // Intervalo entre grupos de zombies en segundos

public:
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;
    AZombie* SpawnZombie(FVector _spawnPosition, FString ZombieGroup);
    void SpawnNextZombieGroup();
    APlant* SpawnPlant(FVector _spawnPosition);

    float TiempoTranscurrido = 0.0f;
    float TiempoTranscurridoSiguientePala = 0.0f;
    float TiempoTranscurridoSiguienteAbono = 0.0f;

    float TiempoTrancurridoSiguienteTarjetaLanzaguisantes = 0.0f;
    float TiempoTrancurridoSiguienteTarjetaGirasol = 0.0f;
    float TiempoTrancurridoSiguienteTarjetaNuez = 0.0f;
    float TiempoTrancurridoSiguienteTarjetaLanzamaiz = 0.0f;

    FTimerHandle TimerHandleTarjetasPlantaNuez;
    FTimerHandle TimerHandlePotenciadoresAgua;
    float IncrementarAguaCada = 20.0f;

    void TimerCallBackPotenciadoresAgua();
    void TimerCallBackTarjetasPlantaNuez();
    void VisualizarPotenciadores();
    void VisualizarTarjetasPlantas();
};



