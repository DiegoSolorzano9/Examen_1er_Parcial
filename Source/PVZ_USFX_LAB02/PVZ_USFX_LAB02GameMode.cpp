// Copyright Epic Games, Inc. All Rights Reserved.
#include "PVZ_USFX_LAB02GameMode.h"
#include "PVZ_USFX_LAB02Pawn.h"
#include "Zombie.h"
#include "Plant.h"
#include "Potenciador.h"
#include "MegaSol.h"
#include "TimerManager.h"

APVZ_USFX_LAB02GameMode::APVZ_USFX_LAB02GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    DefaultPawnClass = APVZ_USFX_LAB02Pawn::StaticClass();

    // Resto de la inicialización de tus mapas y variables aquí
}

void APVZ_USFX_LAB02GameMode::BeginPlay()
{
    Super::BeginPlay();
    float NumberZombies;
    float NumberZombiesPerGroup;
    float InitialZombieSpawnX;
    float InitialZombieSpawnY;  
    float ZombieSpacingX;   
    float ZombieSpawnZ;

    // Resto del código de inicio del juego aquí

    // Crear hordas de zombies
    for (int32 GroupIndex = 0; GroupIndex < NumberZombies / NumberZombiesPerGroup; ++GroupIndex)
    {
        FString ZombieGroupName = FString::Printf(TEXT("Group%d"), GroupIndex);
        for (int32 i = 0; i < NumberZombiesPerGroup; ++i)
        {
            SpawnZombie(FVector(InitialZombieSpawnX + i * ZombieSpacingX, InitialZombieSpawnY, ZombieSpawnZ), ZombieGroupName);
        }
    }
}

void APVZ_USFX_LAB02GameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Resto de la lógica de Tick aquí

    // Comprobar si es el momento de spawnear el siguiente grupo de zombies
    TiempoTranscurrido += DeltaTime;
    if (TiempoTranscurrido >= ZombieGroupSpawnInterval)
    {
        TiempoTranscurrido = 0.0f;
        SpawnNextZombieGroup();
    }
}

AZombie* APVZ_USFX_LAB02GameMode::SpawnZombie(FVector _spawnPosition, FString ZombieGroup)
{
    FTransform SpawnLocation;
    SpawnLocation.SetLocation(_spawnPosition);
    AZombie* NewZombie = GetWorld()->SpawnActor<AZombie>(AZombie::StaticClass(), SpawnLocation);

    // Agregar el zombie al grupo correspondiente en el TMap
    if (NewZombie)
    {
        if (!MapZombieGroups.Contains(ZombieGroup))
        {
            MapZombieGroups.Add(ZombieGroup, TMap<FString, AZombie*>());
        }

        int32 ZombieIndex = MapZombieGroups[ZombieGroup].Num() + 1;
        FString ZombieName = FString::Printf(TEXT("Zombie%d"), ZombieIndex);
        MapZombieGroups[ZombieGroup].Add(ZombieName, NewZombie);
    }

    return NewZombie;
}

void APVZ_USFX_LAB02GameMode::SpawnNextZombieGroup()
{
    float NumberZombies;
    float NumberZombiesPerGroup;
    float InitialZombieSpawnX;
    float InitialZombieSpawnY;
    float ZombieSpacingX;
    float ZombieSpawnZ;
    // Comprobar si hay más grupos de zombies para spawnear
    int32 CurrentGroupIndex = MapZombieGroups.Num();
    if (CurrentGroupIndex < NumberZombies / NumberZombiesPerGroup)
    {
        FString ZombieGroupName = FString::Printf(TEXT("Group%d"), CurrentGroupIndex);
        for (int32 i = 0; i < NumberZombiesPerGroup; ++i)
        {
            SpawnZombie(FVector(InitialZombieSpawnX + i * ZombieSpacingX, InitialZombieSpawnY, ZombieSpawnZ), ZombieGroupName);
        }
    }
}

APlant* APVZ_USFX_LAB02GameMode::SpawnPlant(FVector _spawnPosition)
{
    FTransform SpawnLocation;
    SpawnLocation.SetLocation(_spawnPosition);
    return GetWorld()->SpawnActor<APlant>(APlant::StaticClass(), SpawnLocation);
}

void APVZ_USFX_LAB02GameMode::TimerCallBackPotenciadoresAgua()
{
    MapPotenciadores[TEXT("Agua")] += 1;
}

void APVZ_USFX_LAB02GameMode::TimerCallBackTarjetasPlantaNuez()
{
    MapTarjetasPlantas[TEXT("Nuez")] += 1;
}

void APVZ_USFX_LAB02GameMode::VisualizarPotenciadores()
{
    for (TPair<FString, uint32> ElementoActual : MapPotenciadores)
    {
        FString Llave = ElementoActual.Key;
        int32 Valor = ElementoActual.Value;
        UE_LOG(LogTemp, Warning, TEXT("Llave: %s, Valor: %d"), *Llave, Valor);
    }
}

void APVZ_USFX_LAB02GameMode::VisualizarTarjetasPlantas()
{
    for (TPair<FString, uint32> TarjetaActual : MapTarjetasPlantas)
    {
        FString Llave = TarjetaActual.Key;
        int32 Valor = TarjetaActual.Value;
        UE_LOG(LogTemp, Warning, TEXT("Llave: %s, Valor: %d"), *Llave, Valor);
    }
}
