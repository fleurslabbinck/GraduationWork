#include "PreyVsPredatorGameModeBase.h"

#include "GameFramework/GameUserSettings.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/BaseAnimal/HFSMBTHController.h"
#include "PreyVsPredator/Animals/BaseAnimal/PBTController.h"
#include "PreyVsPredator/Animals/WorldEvents/WorldEventsSubsystem.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


void APreyVsPredatorGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	checkf(WorldGridCellClass != nullptr, TEXT("World Grid Cell Class not assigned"));
	checkf(PreyClass != nullptr, TEXT("Prey Class not assigned"));
	checkf(HFSMBTHPreyControllerClass != nullptr, TEXT("Prey Controller Class not assigned"));
	checkf(PBTPreyControllerClass != nullptr, TEXT("Prey Controller Class not assigned"));

	// Initiate grid
	UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};
	WorldGrid->SetPondSize(PondSize);
	WorldGrid->SetupGrid(WorldGridCellClass, StartPosition, Rows, Columns, CellSize);

	// Spawn entities
	for (uint32 Index{}; Index < MaxAmountPrey; ++Index)
	{
		SpawnEntity();
	}

	// Subscribe to event to always spawn entity when one entity dies
	GetWorld()->GetSubsystem<UWorldEventsSubsystem>()->OnEntityDeath.AddDynamic(this, &APreyVsPredatorGameModeBase::SpawnEntity);

	StartSimulation();
}

void APreyVsPredatorGameModeBase::SpawnEntity()
{
	UWorld* World{GetWorld()};
	const FVector RandomPosition{World->GetSubsystem<UWorldGridSubsystem>()->RandomPositionInGrid()};

	// Always spawn
	FActorSpawnParameters SpawnParameters{};
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn entity
	ABaseEntity* Prey{Cast<ABaseEntity>(World->SpawnActor(PreyClass, &RandomPosition, {}, SpawnParameters))};

	// Spawn appropriate controller
	ABaseController* PreyController{nullptr};
	switch (SimulationMethod)
	{
	case ESimulationMethod::HFSMBTH:
		PreyController = Cast<ABaseController>(World->SpawnActor(HFSMBTHPreyControllerClass));
		break;
	case ESimulationMethod::PBT:
		PreyController = Cast<ABaseController>(World->SpawnActor(PBTPreyControllerClass));
		break;
	}

	checkf(Prey != nullptr, TEXT("Prey did not spawn"));
	checkf(PreyController != nullptr, TEXT("Prey Controller did not spawn"));

	// Posses prey
	PreyController->Possess(Prey);
}

void APreyVsPredatorGameModeBase::StartSimulation()
{
	// Start recording FPS
	GetWorld()->GetTimerManager().SetTimer(m_BenchmarkTimer, this, &APreyVsPredatorGameModeBase::RecordFPS, BenchmarkInterval, true);
	
	// Set timer to end simulation
	FTimerHandle SimulationTimer{};
	GetWorld()->GetTimerManager().SetTimer(SimulationTimer, this, &APreyVsPredatorGameModeBase::EndSimulation, SimulationDuration);
}

void APreyVsPredatorGameModeBase::RecordFPS()
{
	// Current FPS
	double CurrentFPS{1.0 / GetWorld()->GetDeltaSeconds()};
	m_RecordedFPS.Add(CurrentFPS);

	// Log FPS
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, FString::Printf(TEXT("Recorded FPS: %f"), CurrentFPS));
	UE_LOG(LogTemp, Log, TEXT("Recorded FPS: %f"), CurrentFPS);
}

void APreyVsPredatorGameModeBase::EndSimulation()
{
	GetWorld()->GetTimerManager().ClearTimer(m_BenchmarkTimer);
	
	// Save results to a file
	FString Results;
	for (double FPS : m_RecordedFPS)
	{
		Results += FString::SanitizeFloat(FPS) + LINE_TERMINATOR;
	}

	FString SavePath = FPaths::ProjectDir() + TEXT("SimulationFPSMetrics.txt");
	FFileHelper::SaveStringToFile(Results, *SavePath);

	UE_LOG(LogTemp, Log, TEXT("Results saved to: %s"), *SavePath);
}
