#include "UnitHelper.h"
#include "ScriptGlobal.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

void CreateRandomCombatVehicle(Unit &unit, const LOCATION &loc, UnitHelper::VehicleBuilder &vehicleBuilder)
{
	int vehicleChoice = TethysGame::GetRand(10);

	switch (vehicleChoice)
	{
	case 0:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapLynx, loc, map_id::mapMicrowave);
		break;
	case 1:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapLynx, loc, map_id::mapStickyfoam);
		break;
	case 2:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapLynx, loc, map_id::mapRPG);
		break;
	case 3:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapLynx, loc, map_id::mapEMP);
		break;
	case 4:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapLynx, loc, map_id::mapESG);
		break;
	case 5:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapPanther, loc, map_id::mapMicrowave);
		break;
	case 6:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapPanther, loc, map_id::mapStickyfoam);
		break;
	case 7:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapPanther, loc, map_id::mapRPG);
		break;
	case 8:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapPanther, loc, map_id::mapEMP);
		break;
	case 9:
		vehicleBuilder.CreateVechLightsOn(unit, map_id::mapPanther, loc, map_id::mapESG);
		break;
	}
}

void CreateRogueFightGroup(FightGroup &fightGroup, MAP_RECT &mapRect, UnitHelper::VehicleBuilder &vehicleBuilder)
{
	int vechsInFightGroup = 2 + TethysGame::GetRand(4);

	std::vector<Unit> vehicles;

	for (int i = 0; i < vechsInFightGroup; ++i)
	{
		Unit unit;
		CreateRandomCombatVehicle(unit, mapRect.RandPt(), vehicleBuilder);

		vehicles.push_back(unit);
	}

	vehicleBuilder.PopulateFightGroup(fightGroup, vehicles);
	fightGroup.SetRect(mapRect);
}

void CreateSetOfRogueFightGroups(std::vector<FightGroup> &fightGroups, MAP_RECT &mapRect, UnitHelper::VehicleBuilder &vehicleBuilder)
{
	FightGroup fightGroup;
	for (int i = 0; i < 3; ++i)
	{ 
		CreateRogueFightGroup(fightGroup, mapRect, vehicleBuilder);
		fightGroups.push_back(fightGroup);
	}
}

void InitializeRogueStartingUnits(UnitHelper::VehicleBuilder& vehicleBuilder)
{
	const int evacVehiclesStartingLocsSize = 18;
	LOCATION evacVehicleLocs[evacVehiclesStartingLocsSize]
	{
		LOCATION(10 + X_, 55 + Y_),
		LOCATION(10 + X_, 57 + Y_),
		LOCATION(10 + X_, 59 + Y_),
		LOCATION(10 + X_, 61 + Y_),
		LOCATION(10 + X_, 63 + Y_),
		LOCATION(10 + X_, 65 + Y_),
		
		LOCATION(12 + X_, 55 + Y_),
		LOCATION(12 + X_, 57 + Y_),
		LOCATION(12 + X_, 59 + Y_),
		LOCATION(12 + X_, 61 + Y_),
		LOCATION(12 + X_, 63 + Y_),
		LOCATION(12 + X_, 65 + Y_),

		LOCATION(14 + X_, 55 + Y_),
		LOCATION(14 + X_, 57 + Y_),
		LOCATION(14 + X_, 59 + Y_),
		LOCATION(14 + X_, 61 + Y_),
		LOCATION(14 + X_, 63 + Y_),
		LOCATION(14 + X_, 65 + Y_)
	};
	RandomizeList(evacVehiclesStartingLocsSize, evacVehicleLocs);

	std::vector<Unit> units;

	vehicleBuilder.SetPlayer(Player2);
	vehicleBuilder.SetVehicleDirection(UnitDirection::West);

	MAP_RECT failedEvacRect(7 + X_, 53 + Y_, 19 + X_, 64 + Y_);

	Unit vehicle;
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapConVec, evacVehicleLocs[0], map_id::mapCommandCenter);
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapEarthworker, evacVehicleLocs[1], map_id::mapNone);
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapConVec, evacVehicleLocs[2], map_id::mapTokamak);
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapRoboMiner, evacVehicleLocs[3], map_id::mapNone);
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapCargoTruck, evacVehicleLocs[4], map_id::mapNone);
	vehicle.SetTruckCargo(Truck_Cargo::truckFood, 1000);
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapSpider, evacVehicleLocs[5], map_id::mapNone);
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapCargoTruck, evacVehicleLocs[6], map_id::mapNone);
	vehicle.SetTruckCargo(Truck_Cargo::truckCommonMetal, 1000);

	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapCargoTruck, evacVehicleLocs[7], map_id::mapNone);
	vehicle.SetTruckCargo(Truck_Cargo::truckRareMetal, 1000);

	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapEvacuationTransport, evacVehicleLocs[8], map_id::mapNone);

	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapCargoTruck, evacVehicleLocs[9], map_id::mapNone);
	vehicle.SetTruckCargo(Truck_Cargo::truckCommonMetal, 1000);

	std::vector<FightGroup> rogueFightGroups;

	CreateSetOfRogueFightGroups(rogueFightGroups, MAP_RECT(39 + X_, 83 + Y_, 50 + X_, 94 + Y_), vehicleBuilder);
	CreateSetOfRogueFightGroups(rogueFightGroups, MAP_RECT(51 + X_, 53 + Y_, 62 + X_, 65 + Y_), vehicleBuilder);
	CreateSetOfRogueFightGroups(rogueFightGroups, MAP_RECT(49 + X_, 65 + Y_, 58 + X_, 79 + Y_), vehicleBuilder);
	CreateSetOfRogueFightGroups(rogueFightGroups, MAP_RECT(67 + X_, 36 + Y_, 78 + X_, 48 + Y_), vehicleBuilder);
	
	MAP_RECT eastOfDestroyedCCRect(67 + X_, 78 + Y_, 73 + X_, 98 + Y_);

	if (Player[0].Difficulty() == DiffHard)
	{
		CreateRogueFightGroup(scriptGlobal.CommonSmelterAttackGroup, eastOfDestroyedCCRect, vehicleBuilder);
		scriptGlobal.CommonSmelterAttackGroup.SetRect(MAP_RECT(72 + X_, 8 + Y_, 79 + X_, 14 + Y_));
	}

	CreateRogueFightGroup(scriptGlobal.StartingPatrolFightGroup, MAP_RECT(29 + X_, 99 + Y_, 35 + X_, 105 + Y_), vehicleBuilder);
	LOCATION patrolPoints[6];
	patrolPoints[0] = LOCATION(31 + X_, 100 + Y_);
	patrolPoints[1] = LOCATION(70 + X_, 94 + Y_);
	patrolPoints[2] = LOCATION(54 + X_, 67 + Y_);
	patrolPoints[3] = LOCATION(81 + X_, 37 + Y_);
	patrolPoints[4] = LOCATION(-1, -1);

	PatrolRoute patrolRoute;
	patrolRoute.waypoints = patrolPoints;
	scriptGlobal.StartingPatrolFightGroup.SetPatrolMode(patrolRoute);

	CreateSetOfRogueFightGroups(rogueFightGroups, eastOfDestroyedCCRect, vehicleBuilder);
	CreateSetOfRogueFightGroups(rogueFightGroups, MAP_RECT(68 + X_, 50 + Y_, 78 + X_, 69 + Y_), vehicleBuilder);
	CreateSetOfRogueFightGroups(rogueFightGroups, MAP_RECT(84 + X_, 32 + Y_, 89 + X_, 59 + Y_), vehicleBuilder);
	CreateSetOfRogueFightGroups(rogueFightGroups, MAP_RECT(37 + X_, 16 + Y_, 51 + X_, 29 + Y_), vehicleBuilder);
	//CreateSetOfRogueFightGroups(rogueFightGroups, MAP_RECT(19 + X_, 30 + Y_, 29 + X_, 40 + Y_), vehicleBuilder);

	MAP_RECT commonMineRect = MAP_RECT(LOCATION(63 + X_, 20 + Y_), LOCATION(83 + X_, 31 + Y_));
	MAP_RECT rareMineRect = MAP_RECT(LOCATION(3 + X_, 98 + Y_), LOCATION(16 + X_, 111 + Y_));

	vehicleBuilder.CreateTrucksInRect(units, commonMineRect, Truck_Cargo::truckCommonOre, std::vector<int> {321, 318, 315, 0, 326});
	vehicleBuilder.CreateTrucksInRect(units, rareMineRect, Truck_Cargo::truckRareOre, std::vector<int> {121, 126, 105, 0 });

	CreateSetOfRogueFightGroups(rogueFightGroups, commonMineRect, vehicleBuilder);
	CreateSetOfRogueFightGroups(rogueFightGroups, rareMineRect, vehicleBuilder);
	CreateSetOfRogueFightGroups(rogueFightGroups, failedEvacRect, vehicleBuilder);

	std::copy(rogueFightGroups.begin(), rogueFightGroups.end(), scriptGlobal.RogueFightGroups);

	const int vehicleLocsSize = 10;
	LOCATION vehicleLocs[vehicleLocsSize] 
	{
		LOCATION(30 + X_, 74 + Y_),
		LOCATION(42 + X_, 51 + Y_),
		LOCATION(35 + X_, 65 + Y_),
		LOCATION(76 + X_, 28 + Y_),
		LOCATION(31 + X_, 112 + Y_),
		LOCATION(41 + X_, 58 + Y_),
		LOCATION(26 + X_, 84 + Y_),
		LOCATION(50 + X_, 42 + Y_),
		LOCATION(48 + X_, 110 + Y_),
		LOCATION(68 + X_, 10 + Y_)
	};

	RandomizeList(vehicleLocsSize, vehicleLocs);

	vehicleBuilder.SetVehicleDirection(UnitHelper::GetRandomUnitDirection());
	TethysGame::CreateUnit(vehicle, map_id::mapCargoTruck, vehicleLocs[0], Player2, map_id::mapNone, 0);

	vehicleBuilder.SetVehicleDirection(UnitHelper::GetRandomUnitDirection());
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapEarthworker, vehicleLocs[1], map_id::mapNone);

	vehicleBuilder.SetVehicleDirection(UnitHelper::GetRandomUnitDirection());
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapConVec, vehicleLocs[2], map_id::mapNone);

	vehicleBuilder.SetVehicleDirection(UnitHelper::GetRandomUnitDirection());
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapConVec, vehicleLocs[3], map_id::mapNone);

	vehicleBuilder.SetVehicleDirection(UnitHelper::GetRandomUnitDirection());
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapConVec, vehicleLocs[4], map_id::mapNone);

	vehicleBuilder.SetVehicleDirection(UnitHelper::GetRandomUnitDirection());
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapEvacuationTransport, vehicleLocs[5], map_id::mapNone);

	vehicleBuilder.SetVehicleDirection(UnitHelper::GetRandomUnitDirection());
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapRoboSurveyor, vehicleLocs[6], map_id::mapNone);

	vehicleBuilder.SetVehicleDirection(UnitHelper::GetRandomUnitDirection());
	vehicleBuilder.CreateVechLightsOn(vehicle, map_id::mapRoboDozer, vehicleLocs[7], map_id::mapNone);
}
