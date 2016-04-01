#include "MapHelper.h"
#include "Disasters.h"
#include "UnitHelper.h"
#include "VehicleCounter.h"
#include "ScriptGlobal.h"
#include "Briefing.h"
#include "HFL\Source\HFL.h"
#include "OP2Helper\OP2Helper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetails("Campaign - Ply, Pursued, Ep 1 - Evac Under Fire", "SandyValley.map", "PursuedTechTree.txt", MissionTypes::Colony, 3);

extern SongIds PlayList[];
extern void InitializeStartingUnits(UnitHelper::VehicleBuilder &vehicleBuilder);
extern void InitializeRogueStartingUnits(UnitHelper::VehicleBuilder &vehicleBuilder);
extern void InitializeVictoryConditions();
ScriptGlobal scriptGlobal;

UnitHelper::VehicleBuilder vehicleBuilder;
UnitHelper::VehicleCounter vehicleCounter;

ExportSaveLoadData(scriptGlobal);

void InitializeAIHelperClasses()
{
	vehicleBuilder.SetPlayer(Player0);
	vehicleBuilder.SetVehicleDirection(UnitDirection::South);
}

void InitializeEdenStartingUnits()
{
	std::vector<Unit> units;

	vehicleBuilder.SetPlayer(Player1);

	MAP_RECT idleTigersRect(LOCATION(100 + X_, 31 + Y_), LOCATION(127 + X_, 127 + Y_));
	MAP_RECT idlePanthersRect(LOCATION(93 + X_, 2 + Y_), LOCATION(126 + X_, 27 + Y_));

	vehicleBuilder.CreateVehiclesInRect(units, idleTigersRect, map_id::mapTiger,
		std::vector<map_id> { mapAcidCloud, mapThorsHammer, mapEMP, mapRailGun, mapAcidCloud, mapThorsHammer, mapEMP, mapRailGun,
		mapAcidCloud, mapThorsHammer, mapEMP, mapRailGun, mapAcidCloud, mapThorsHammer, mapEMP, mapRailGun,
		mapAcidCloud, mapThorsHammer, mapEMP, mapRailGun, mapAcidCloud, mapThorsHammer, mapEMP, mapRailGun,
		mapAcidCloud, mapThorsHammer, mapEMP, mapRailGun, mapAcidCloud, mapThorsHammer, mapEMP, mapRailGun });

	vehicleBuilder.PopulateFightGroup(scriptGlobal.IdleTigers, units);
	scriptGlobal.IdleTigers.SetRect(idleTigersRect);
	units.clear();

	vehicleBuilder.CreateVehiclesInRect(units, idlePanthersRect, map_id::mapPanther, 
		std::vector<map_id> { mapLaser, mapRailGun, mapEMP, mapLaser, mapRailGun, mapEMP, mapLaser, mapEMP, 
		mapRailGun, mapLaser, mapEMP, mapRailGun, mapLaser, mapRailGun, mapEMP, mapLaser, mapRailGun, mapEMP, 
		mapLaser, mapEMP, mapRailGun, mapLaser, mapEMP, mapRailGun });

	vehicleBuilder.PopulateFightGroup(scriptGlobal.IdlePanthers, units);
	scriptGlobal.IdlePanthers.SetRect(idlePanthersRect);
	units.clear();
}

void InitializeMiningBeacons()
{
	MapHelper::CreateBeaconRandomYield(LOCATION(91 + X_, 4 + Y_), BeaconTypes::OreTypeCommon);
	MapHelper::CreateBeaconRandomYield(LOCATION(111 + X_, 15 + Y_), BeaconTypes::OreTypeCommon);
	MapHelper::CreateBeaconRandomYield(LOCATION(6 + X_, 112 + Y_), BeaconTypes::OreTypeRare);
	MapHelper::CreateBeaconRandomYield(LOCATION(102 + X_, 107 + Y_), BeaconTypes::OreTypeCommon);
	MapHelper::CreateBeaconRandomYield(LOCATION(118 + X_, 68 + Y_), BeaconTypes::OreTypeRare);
}

void InitializeFumarolesAndVents()
{
	std::vector<LOCATION> possLocs{ LOCATION(20 + X_, 33 + Y_), LOCATION(19 + X_, 39 + Y_), 
		LOCATION(28 + X_, 38 + Y_), LOCATION(29 + X_, 34 + Y_) };
	MapHelper::CreateFumarolesFromRandomLocs(3, possLocs);

	MapHelper::CreateMagmaWellInRegion(MAP_RECT(2 + X_, 34 + Y_, 9 + X_, 43 + Y_));
}

void InitializeDisasterTrigger()
{
	int disasterTimeMin = 3500;
	int disasterTimeMax = 7000;

	if (Player[0].Difficulty() == 1)
	{
		disasterTimeMin = 3000;
		disasterTimeMax = 6500;
	}
	else if (Player[0].Difficulty() == 2)
	{
		disasterTimeMin = 2000;
		disasterTimeMax = 5500;
	}

	scriptGlobal.TrigDisaster = CreateTimeTrigger(false, false, disasterTimeMin, disasterTimeMax, "InitializeRandomDisaster");
}

void SetMultipleResearchedTechs(int playerNumb, std::vector<int> completedResearch)
{
	for (int techID : completedResearch)
	{
		Player[0].MarkResearchComplete(techID);
	}
}

void SetResearchedTech()
{
	//3401 Removed (cybernetic teleoperation).
	//05052 Removed (Garage)
	SetMultipleResearchedTechs(Player0, std::vector<int> { 2701, 2702, 2703, 2704, 2705, 3406, 3301, 3408, 7206, 7103, 8307, 5305,
		3303, 3402, 3405, 3302, 3304, 3305, 3201, 3202, 3901, 3306, 3851, 5110, 5201, 5202, 5111, 5317, 5508, 5116, 5599, 5307 });
}

Export int InitProc()
{
	HFLInit();

	ShowBriefing();

	TethysGame::SetDaylightEverywhere(true);
	TethysGame::SetDaylightMoves(false);

	Player[0].CenterViewOn(15 + X_, 5 + Y_);

	Player[0].GoPlymouth();
	Player[0].SetColorNumber(PlayerColor::PlayerRed);
	Player[0].GoHuman();
	Player[0].SetKids(30);
	Player[0].SetWorkers(40);
	Player[0].SetScientists(25);
	Player[0].SetFoodStored(9000);
	TethysGame::ForceMoraleOK(Player0);
	TethysGame::ForceMoraleOK(Player0);
	SetResearchedTech();

	if (Player[0].Difficulty() == PlayerDifficulty::DiffEasy)
	{
		TethysGame::ForceMoraleGreat(Player0);
		TethysGame::ForceMoraleGreat(Player0);
		Player[0].SetWorkers(50);
		Player[0].SetFoodStored(13'000);
	}
	else if (Player[0].Difficulty() == PlayerDifficulty::DiffNormal)
	{
		Player[0].SetWorkers(45);
		Player[0].SetFoodStored(11'000);
	}


	Player[1].GoEden();
	Player[1].SetColorNumber((int)PlayerColor::PlayerBlue);
	Player[1].GoAI();
	TethysGame::ForceMoraleGood(Player1);
	TethysGame::ForceMoraleGood(Player1);

	Player[2].GoPlymouth();
	Player[2].SetColorNumber(PlayerColor::PlayerYellow);
	Player[2].GoAI();
	TethysGame::ForceMoraleGood(Player2);
	TethysGame::ForceMoraleGood(Player2);

	InitializeMiningBeacons();

	InitializeFumarolesAndVents();

	InitializeDisasterTrigger();

	InitializeVictoryConditions();

	InitializeAIHelperClasses();

	scriptGlobal.TrigFailureWaitTime = CreateTimeTrigger(false, false, 90, "NoResponseToTrigger");
	CreateFailureCondition(true, true, scriptGlobal.TrigFailureWaitTime, "Ignored");

	InitializeStartingUnits(vehicleBuilder);
	InitializeEdenStartingUnits();
	InitializeRogueStartingUnits(vehicleBuilder);

	if (Player[0].Difficulty() == PlayerDifficulty::DiffHard)
	{
		scriptGlobal.TrigReleaseRogueFightGroup = CreateTimeTrigger(false, false, 4000, 7000, "ReleaseRogueFightGroup");
	}
	else
	{
		scriptGlobal.TrigReleaseRogueFightGroup = CreateTimeTrigger(false, false, 5000, 9000, "ReleaseRogueFightGroup");
	}

	for (int i = 0; i < scriptGlobal.RogueFightGroupsCount; ++i)
	{
		scriptGlobal.RogueFightGroupsAvailable[i] = true;
	}

	TethysGame::SetMusicPlayList(4, 0, PlayList);

	Unit marker;
	TethysGame::PlaceMarker(marker, 13 + X_, 6 + Y_, MarkerTypes::Circle);

	return true;
}

int GetPopulation(PlayerNum playerNum)
{
	return Player[playerNum].Kids() + Player[playerNum].Workers() + Player[playerNum].Scientists();
}

bool CheckIfGameFailed()
{
	Player[0].resetChecks();

	if (Player[0].Workers() < 8)
	{
		return true;
	}
	else if (Player[0].Scientists() < 3)
	{
		return true;
	}
	else if (GetPopulation(Player0) < 50)
	{
		return true;
	}
	else if (!UnitHelper::BuildingOrKitAvailable(Player0, map_id::mapCommandCenter) && 
		     !UnitHelper::BuildingOrKitAvailable(Player2, map_id::mapCommandCenter))
	{
		return true;
	}
	else if (!UnitHelper::BuildingOrKitAvailable(Player0, map_id::mapStructureFactory))
	{
		return true;
	}
	else if (!scriptGlobal.ScoutCommander.IsLive())
	{
		return true;
	}

	return false;
}

void VehicleCommandLinkCompromiseEffect()
{
	// Note: Using the Modulus operator to make compromise only occur about every 3-4 marks.
	if (TethysGame::Time() % 75 == 0)
	{
		TethysGame::AddMessage(140 * 32, 1 * 32, "Vehicle Command Link Compromised.", Player0, SoundID::sndBeep9);

		PlayerVehicleEnum playerVehicleEnum = PlayerVehicleEnum(Player0);

		Unit vehicle;
		LOCATION loc;
		while (playerVehicleEnum.GetNext(vehicle))
		{
			loc = LOCATION(TethysGame::GetRand(128) + X_, TethysGame::GetRand(128) + Y_);
			vehicle.DoMove(loc);
		}
	}
}

bool CommandCenterBuiltInSafeRect()
{
	Unit commandCenter;
	if (UnitHelper::GetFirstBuildingOfType(commandCenter, Player0, map_id::mapCommandCenter))
	{
		MAP_RECT commandCenterSafeRect(18 + X_, 32 + Y_, 30 + X_, 40 + Y_);

		if (commandCenterSafeRect.Check(commandCenter.Location()))
		{
			return true;
		}
	}

	return false;
}

void SetHumanCommandCenterEstablished()
{
	Unit building;
	UnitHelper::GetFirstBuildingOfType(building, Player0, map_id::mapCommandCenter);

	TethysGame::AddMessage(building, "Command Center Heat Signature Hidden by Fumarole Activity!", Player0, SoundID::sndBeep9);
	scriptGlobal.CommandCenterBuilt = true;
	scriptGlobal.TrigReleaseRogueFightGroup.Enable();
	scriptGlobal.TrigDisaster.Enable();
}

bool CheckHumanBuildingCount()
{
	int oldBuildingCount = scriptGlobal.NumberOfHumanBuildings;
	
	int currentBuildingCount = UnitHelper::CountAllBuildings(Player0);

	scriptGlobal.NumberOfHumanBuildings = currentBuildingCount;

	if (currentBuildingCount <= oldBuildingCount)
	{
		return true;
	}

	if (!scriptGlobal.CommandCenterBuilt && CommandCenterBuiltInSafeRect())
	{		
		SetHumanCommandCenterEstablished();
		return true;
	}

	return false;
}

void WakeEnemyForces()
{
	scriptGlobal.IdleTigers.DoAttackEnemy();
	scriptGlobal.IdlePanthers.DoAttackEnemy();
	TethysGame::AddMessage(105 * 32, 63 * 32, "We Have Been Located by Eden!", Player0, SoundID::sndBeep9);
	scriptGlobal.EnemyAwake = true;
}

bool CheckHumanForcesTooFarEast()
{
	return UnitHelper::VehicleInRectangle(MAP_RECT(88 + X_, 0 + Y_, 128 + X_, 128 + Y_), Player0);
}

Export void AIProc()
{
	if (CheckIfGameFailed())
	{
		scriptGlobal.TrigFailureWaitTime.Enable();
	}

	if (!scriptGlobal.EnemyAwake && !CheckHumanBuildingCount())
	{
		WakeEnemyForces();
	}

	if (scriptGlobal.EnemyAwake)
	{
		VehicleCommandLinkCompromiseEffect();
	}

	if (!scriptGlobal.EnemyAwake)
	{
		if (scriptGlobal.IdleTigers.HasBeenAttacked() ||
			scriptGlobal.IdlePanthers.HasBeenAttacked() ||
			CheckHumanForcesTooFarEast())
		{
			WakeEnemyForces();
		}
	}
}

Export void NoResponseToTrigger() { }

Export void InitializeRandomDisaster()
{
	std::vector<LOCATION> criticalBuildingLocations;

	UnitHelper::FindBuildingLocations(criticalBuildingLocations, Player0,
		std::vector<map_id> { map_id::mapCommandCenter, map_id::mapStructureFactory, map_id::mapCommonOreSmelter, map_id::mapGORF, map_id::mapVehicleFactory });

	CreateRandomDisaster(criticalBuildingLocations);
}

void buildRogueFightGroupPatrol(FightGroup &fightGroup)
{
	LOCATION PatrolPoints[6];
	MAP_RECT mapRect(X_, Y_, 72 + X_, 128 + Y_);

	for (int i = 0; i < 5; i++)
	{
		PatrolPoints[i] = mapRect.RandPt();
	}
	PatrolPoints[5] = LOCATION(-1, -1);

	PatrolRoute patrolRoute;
	patrolRoute.waypoints = PatrolPoints;
	
	if (TethysGame::GetRand(5) < 3)
	{ 
		fightGroup.DoPatrolOnly();
	}

	fightGroup.SetPatrolMode(patrolRoute);
}

void SelfDestructFightGroup(FightGroup &fightGroup)
{
	Unit vehicle;
	GroupEnumerator groupEnumerator(fightGroup);

	while (groupEnumerator.GetNext(vehicle))
	{
		vehicle.DoSelfDestruct();
	}
}

void ReviewRogueFightGroupsStatus(std::vector<int> &availableFightGroupIndices)
{
	for (int i = 0; i < scriptGlobal.RogueFightGroupsCount; ++i)
	{
		if (scriptGlobal.RogueFightGroups[i].TotalUnitCount() == 0)
		{
			scriptGlobal.RogueFightGroupsAvailable[i] = false;
			continue;
		}

		if (scriptGlobal.RogueFightGroupsAvailable[i])
		{
			availableFightGroupIndices.push_back(i);
		}
	}

	if (availableFightGroupIndices.size() < 4)
	{
		WakeEnemyForces();
	}
}

void SetRogueFightGroupAction(int indexToSend)
{
	scriptGlobal.RogueFightGroupsAvailable[indexToSend] = false;

	if (TethysGame::GetRand(10) > 8)
	{
		SelfDestructFightGroup(scriptGlobal.RogueFightGroups[indexToSend]);
	}
	else
	{
		buildRogueFightGroupPatrol(scriptGlobal.RogueFightGroups[indexToSend]);
	}
}

Export void ReleaseRogueFightGroup()
{
	std::vector<int> availableFightGroupIndices;

	ReviewRogueFightGroupsStatus(availableFightGroupIndices);

	if (availableFightGroupIndices.size() > 0)
	{
		int indexToSend = TethysGame::GetRand(availableFightGroupIndices.size());
		SetRogueFightGroupAction(indexToSend);
	}
}