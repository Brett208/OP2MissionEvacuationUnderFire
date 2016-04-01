#include "RubbleMaker.h"
#include "UnitHelper.h"
#include "ScriptGlobal.h"
#include "OP2Helper\OP2Helper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <array>
#include <vector>

void InitializeBlastedTiles(RubbleMaker &rubbleMaker)
{
	rubbleMaker.CreateBlastedTiles(MAP_RECT(85 + X_, 64 + Y_, 103 + X_, 78 + Y_), 40);
	rubbleMaker.CreateBlastedTiles(MAP_RECT(88 + X_, 10 + Y_, 101 + X_, 22 + Y_), 15);
	rubbleMaker.CreateBlastedTiles(MAP_RECT(51 + X_, 65 + Y_, 61 + X_, 70 + Y_), 15);
	rubbleMaker.CreateBlastedTiles(MAP_RECT(86 + X_, 29 + Y_, 100 + X_, 42 + Y_), 10);
	rubbleMaker.CreateBlastedTiles(MAP_RECT(83 + X_, 93 + Y_, 96 + X_, 103 + Y_), 10);
	rubbleMaker.CreateBlastedTiles(MAP_RECT(35 + X_, 89 + Y_, 52 + X_, 100 + Y_), 15);
	rubbleMaker.CreateBlastedTiles(MAP_RECT(63 + X_, 24 + Y_, 80 + X_, 48 + Y_), 15);

	rubbleMaker.CreateBlastedTiles(std::vector<LOCATION>{
		LOCATION(83 + X_, 47 + Y_),
			LOCATION(88 + X_, 40 + Y_),
			LOCATION(88 + X_, 67 + Y_),
			LOCATION(35 + X_, 102 + Y_),
			LOCATION(43 + X_, 90 + Y_),
			LOCATION(51 + X_, 69 + Y_),
			LOCATION(57 + X_, 67 + Y_),
			LOCATION(48 + X_, 61 + Y_),
			LOCATION(62 + X_, 52 + Y_),
			LOCATION(112 + X_, 113 + Y_),
			LOCATION(52 + X_, 60 + Y_),
			LOCATION(48 + X_, 52 + Y_),
			LOCATION(42 + X_, 66 + Y_),
			LOCATION(59 + X_, 61 + Y_),
			LOCATION(61 + X_, 70 + Y_),
			LOCATION(33 + X_, 82 + Y_),
			LOCATION(23 + X_, 84 + Y_),
			LOCATION(14 + X_, 112 + Y_),
			LOCATION(17 + X_, 104 + Y_),
			LOCATION(27 + X_, 102 + Y_),
			LOCATION(47 + X_, 44 + Y_),
			LOCATION(31 + X_, 73 + Y_),
			LOCATION(66 + X_, 94 + Y_),
			LOCATION(59 + X_, 99 + Y_),
			LOCATION(64 + X_, 100 + Y_),
			LOCATION(56 + X_, 80 + Y_)
	});
}

void InitializeStartingVehiclePatrol(UnitHelper::VehicleBuilder &vehicleBuilder)
{
	std::vector<Unit> units;

	//NOTE: These commented out vechs are for testing victory conditions.
	//std::vector<map_id> turrets{ map_id::mapMicrowave, map_id::mapStickyfoam, map_id::mapRPG, map_id::mapEMP, map_id::mapESG };
	//vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(), UnitDirection::South, 1, map_id::mapLynx, turrets);
	//vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(), UnitDirection::South, 1, map_id::mapPanther, turrets);

	vehicleBuilder.CreateLineOfVehicles(units, LOCATION(8 + X_, 1 + Y_), UnitDirection::East, 2, map_id::mapPanther,
		std::vector<map_id> { map_id::mapMicrowave, map_id::mapMicrowave, map_id::mapStickyfoam, map_id::mapRPG, map_id::mapRPG, map_id::mapEMP, map_id::mapEMP, map_id::mapEMP, map_id::mapEMP, map_id::mapESG });

	vehicleBuilder.MoveRelativeAmount(units, LOCATION(0, 3));
	units.clear();

	vehicleBuilder.CreateLineOfVehicles(units, LOCATION(8 + X_, 3 + Y_), UnitDirection::East, 2, map_id::mapSpider, map_id::mapNone, 8);

	vehicleBuilder.MoveRelativeAmount(units, LOCATION(0, 3));
	units.clear();

	vehicleBuilder.CreateLineOfVehicles(units, LOCATION(8 + X_, 5 + Y_), UnitDirection::East, 2, map_id::mapLynx,
		std::vector<map_id>{map_id::mapMicrowave, map_id::mapMicrowave, map_id::mapMicrowave, map_id::mapMicrowave,
		map_id::mapStickyfoam, map_id::mapStickyfoam, map_id::mapRPG, map_id::mapRPG, map_id::mapRPG, map_id::mapRPG});

	vehicleBuilder.MoveRelativeAmount(units, LOCATION(0, 3));
	units.clear();

	vehicleBuilder.CreateLineOfVehicles(units, LOCATION(8 + X_, 7 + Y_), UnitDirection::East, 2, map_id::mapLynx,
		std::vector<map_id>{ map_id::mapEMP, map_id::mapEMP, map_id::mapEMP, map_id::mapEMP, map_id::mapESG, map_id::mapESG});

	vehicleBuilder.MoveRelativeAmount(units, LOCATION(0, 3));
	units.clear();

	vehicleBuilder.CreateVechLightsOn(scriptGlobal.ScoutCommander, map_id::mapScout, LOCATION(14 + X_, 11 + Y_), map_id::mapNone);
	scriptGlobal.ScoutCommander.DoMove(scriptGlobal.ScoutCommander.Location() + LOCATION(0, 3));

	if (Player[0].Difficulty() == PlayerDifficulty::DiffEasy)
	{
		vehicleBuilder.CreateLineOfVehicles(units, LOCATION(8 + X_, 9 + Y_), UnitDirection::East, 2, map_id::mapLynx, map_id::mapRPG, 6);
		vehicleBuilder.MoveRelativeAmount(units, LOCATION(0, 3));
		units.clear();
	}
	else if (Player[0].Difficulty() == PlayerDifficulty::DiffNormal)
	{
		vehicleBuilder.CreateLineOfVehicles(units, LOCATION(8 + X_, 9 + Y_), UnitDirection::East, 2, map_id::mapLynx, map_id::mapRPG, 3);
		vehicleBuilder.MoveRelativeAmount(units, LOCATION(0, 3));
		units.clear();
	}
}

void InitializeStartingUnits(UnitHelper::VehicleBuilder &vehicleBuilder)
{
	RubbleMaker rubbleMaker = RubbleMaker();

	InitializeStartingVehiclePatrol(vehicleBuilder);

	UnitEx building;
	TethysGame::CreateUnit(building, map_id::mapRareOreSmelter, LOCATION(23 + X_, 107 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 41);

	TethysGame::CreateUnit(building, map_id::mapCommonOreSmelter, LOCATION(76 + X_, 11 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 33);

	CreateTubeOrWallLine(76 + X_, 14 + Y_, 76 + X_, 19 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(78 + X_, 19 + Y_, 78 + X_, 19 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(38 + X_, 71 + Y_, 39 + X_, 71 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(40 + X_, 68 + Y_, 40 + X_, 69 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapStructureFactory, LOCATION(40 + X_, 65 + Y_), Player0, map_id::mapNone, 0);
	building.SetFactoryCargo(0, map_id::mapStructureFactory, map_id::mapNone);
	building.SetFactoryCargo(1, map_id::mapCommonOreSmelter, map_id::mapNone);
	building.SetFactoryCargo(2, map_id::mapRareStorage, map_id::mapNone);
	vehicleBuilder.SetPercentDamaged(building, 72);

	CreateTubeOrWallLine(43 + X_, 65 + Y_, 47 + X_, 65 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapVehicleFactory, LOCATION(29 + X_, 79 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 30);

	CreateTubeOrWallLine(32 + X_, 79 + Y_, 35 + X_, 79 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapGORF, LOCATION(44 + X_, 55 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 54);

	TethysGame::CreateUnit(building, map_id::mapRobotCommand, LOCATION(45 + X_, 60 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 93);

	//GORF to RCC
	CreateTubeOrWallLine(44 + X_, 57 + Y_, 44 + X_, 58 + Y_, map_id::mapTube);

	//RCC to Struct Factory
	CreateTubeOrWallLine(45 + X_, 62 + Y_, 45 + X_, 64 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapResidence, LOCATION(23 + X_, 74 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 80);

	//Residence to Destroyed Residence
	TethysGame::CreateWallOrTube(25 + X_, 74 + Y_, -1, map_id::mapTube);

	map_id powerPlantType = map_id::mapMHDGenerator;
	if (Player[0].Difficulty() == PlayerDifficulty::DiffHard)
	{
		powerPlantType = map_id::mapTokamak;
	}

	TethysGame::CreateUnit(building, powerPlantType, LOCATION(35 + X_, 117 + Y_), Player0, map_id::mapNone, 0);

	TethysGame::CreateUnit(building, map_id::mapRecreationFacility, LOCATION(40 + X_, 44 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 35);

	TethysGame::CreateUnit(building, map_id::mapGarage, LOCATION(31 + X_, 87 + Y_), Player0, map_id::mapNone, 0);
	
	Unit vehicle;
	vehicleBuilder.SetVehicleDirection(UnitDirection::West);

	if (Player[0].Difficulty() != DiffEasy)
	{
		vehicleBuilder.SetPlayer(PlayerNum::Player2);
	}
	vehicleBuilder.CreateVehicleInGarage(building, 0, map_id::mapLynx, map_id::mapRPG);
	vehicleBuilder.CreateVehicleInGarage(building, 1, map_id::mapConVec, map_id::mapAgridome);
	vehicleBuilder.SetPercentDamaged(building, 33);

	vehicleBuilder.SetPlayer(PlayerNum::Player0);

	TethysGame::CreateUnit(building, map_id::mapGarage, LOCATION(53 + X_, 47 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 48);

	if (Player[0].Difficulty() != DiffEasy)
	{
		vehicleBuilder.SetPlayer(PlayerNum::Player2);
	}

	vehicleBuilder.CreateVehicleInGarage(building, 0, Truck_Cargo::truckFood, 1000);
	vehicleBuilder.CreateVehicleInGarage(building, 1, map_id::mapPanther, map_id::mapRPG);
	vehicleBuilder.CreateVehicleInGarage(building, 2, Truck_Cargo::truckCommonMetal, 1000);
	vehicleBuilder.SetPlayer(PlayerNum::Player0);

	TethysGame::CreateUnit(building, map_id::mapCommonStorage, LOCATION(38 + X_, 55 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 35);

	CreateTubeOrWallLine(40 + X_, 55 + Y_, 42 + X_, 55 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapResidence, LOCATION(27 + X_, 74 + Y_));
	CreateTubeOrWallLine(27 + X_, 76 + Y_, 27 + X_, 77 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapCommandCenter, LOCATION(49 + X_, 66 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapVehicleFactory, LOCATION(38 + X_, 79 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapCommonOreSmelter, LOCATION(81 + X_, 19 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapTokamak, LOCATION(58 + X_, 60 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapTokamak, LOCATION(18 + X_, 81 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapRareOreSmelter, LOCATION(21 + X_, 100 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapAgridome, LOCATION(35 + X_, 71 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapRecreationFacility, LOCATION(45 + X_, 44 + Y_));

	// Destroyed Rec Center to Destroyed University
	CreateTubeOrWallLine(45 + X_, 47 + Y_, 45 + X_, 45 + Y_, map_id::mapTube);

	// Rec Center to Destroyed Rec Center
	CreateTubeOrWallLine(42 + X_, 44 + Y_, 43 + X_, 44 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapGarage, LOCATION(39 + X_, 87 + Y_));
	
	rubbleMaker.CreateDestroyedBuilding(map_id::mapNursery, LOCATION(40 + X_, 49 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapUniversity, LOCATION(45 + X_, 49 + Y_));

	CreateTubeOrWallLine(44 + X_, 51 + Y_, 44 + X_, 53 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(42 + X_, 49 + Y_, 43 + X_, 49 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapGuardPost, LOCATION(35 + X_, 42 + Y_), Player0, map_id::mapESG, 0);
	vehicleBuilder.SetPercentDamaged(building, 6);

	TethysGame::CreateUnit(building, map_id::mapGuardPost, LOCATION(28 + X_, 42 + Y_), Player0, map_id::mapRPG, 0);
	vehicleBuilder.SetPercentDamaged(building, 0);

	CreateTubeOrWallLine(30 + X_, 42 + Y_, 34 + X_, 42 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapCommonOreMine, LOCATION(6 + X_, 112 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapCommonOreMine, LOCATION(91 + X_, 4 + Y_));

	rubbleMaker.CreateDestroyedBuilding(map_id::mapAgridome, LOCATION(61 + X_, 47 + Y_));
	TethysGame::CreateUnit(building, map_id::mapAgridome, LOCATION(61 + X_, 44 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 35);

	TethysGame::CreateUnit(building, map_id::mapResidence, LOCATION(61 + X_, 38 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 35);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapResidence, LOCATION(66 + X_, 38 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapResidence, LOCATION(71 + X_, 38 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapResidence, LOCATION(76 + X_, 38 + Y_));

	TethysGame::CreateUnit(building, map_id::mapAgridome, LOCATION(41 + X_, 71 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 35);

	//From Agridome to destroyed Vech factory
	CreateTubeOrWallLine(35 + X_, 73 + Y_, 35 + X_, 75 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(36 + X_, 75 + Y_, 37 + X_, 75 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(37 + X_, 76 + Y_, 37 + X_, 77 + Y_, map_id::mapTube);

	//From destroyed vech factory to destroyed garage.
	CreateTubeOrWallLine(38 + X_, 82 + Y_, 38 + X_, 85 + Y_, map_id::mapTube);

	//From destroyed garage to garage
	CreateTubeOrWallLine(34 + X_, 87 + Y_, 37 + X_, 87 + Y_, map_id::mapTube);

	//Destroyed Nursery to GORF/Common ore storage.
	CreateTubeOrWallLine(40 + X_, 51 + Y_, 40 + X_, 54 + Y_, map_id::mapTube);

	//University to Garage to Destroyed Agridome
	CreateTubeOrWallLine(47 + X_, 49 + Y_, 80 + X_, 49 + Y_, map_id::mapTube);

	//Residence to Agridome
	CreateTubeOrWallLine(61 + X_, 40 + Y_, 61 + X_, 42 + Y_, map_id::mapTube);

	//4 Residences (3 destroyed)
	CreateTubeOrWallLine(62 + X_, 40 + Y_, 81 + X_, 40 + Y_, map_id::mapTube);

	//4 Residences to Destroyed Spaceport
	CreateTubeOrWallLine(81 + X_, 31 + Y_, 81 + X_, 49 + Y_, map_id::mapTube);

	//Command Center to Agridome Alternate Route
	CreateTubeOrWallLine(49 + X_, 68 + Y_, 49 + X_, 71 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(48 + X_, 71 + Y_, 44 + X_, 71 + Y_, map_id::mapTube);

	//Completes GORF to Destroyed University
	TethysGame::CreateWallOrTube(45 + X_, 51 + Y_, -1, map_id::mapTube);

	//Rare Ore Smelter to Rare Ore Smelter
	CreateTubeOrWallLine(21 + X_, 103 + Y_, 21 + X_, 105 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapStandardLab, LOCATION(39 + X_, 93 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapAdvancedLab, LOCATION(66 + X_, 29 + Y_));

	//Destroyed Advanced Lab to Destroyed Residence
	CreateTubeOrWallLine(66 + X_, 36 + Y_, 66 + X_, 32 + Y_, map_id::mapTube);

	//Destroyed Garage to Destroyed Standard Lab
	CreateTubeOrWallLine(39 + X_, 89 + Y_, 39 + X_, 91 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapBasicLab, LOCATION(39 + X_, 99 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 16);

	//Destroyed Standard Lab to Basic Lab
	CreateTubeOrWallLine(39 + X_, 95 + Y_, 39 + X_, 98 + Y_, map_id::mapTube);

	//Basic Lab to Destroyed Arachnid Factory to Destroyed RCC
	CreateTubeOrWallLine(41 + X_, 99 + Y_, 53 + X_, 99 + Y_, map_id::mapTube);

	//Destroyed RCC to Arachnid Factory
	CreateTubeOrWallLine(53 + X_, 100 + Y_, 53 + X_, 102 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapGORF, LOCATION(31 + X_, 98 + Y_));

	//Basic Lab to Destroyed GORF
	CreateTubeOrWallLine(34 + X_, 98 + Y_, 37 + X_, 98 + Y_, map_id::mapTube);

	//Destroyed Rare Ore Smelter to Destroyed GORF
	CreateTubeOrWallLine(24 + X_, 100 + Y_, 31 + X_, 100 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapSpaceport, LOCATION(77 + X_, 29 + Y_));

	rubbleMaker.CreateDestroyedBuilding(map_id::mapRareOreSmelter, LOCATION(32 + X_, 107 + Y_));

	//Rare Ore Smelter to Destroyed Rare Ore Smelter
	CreateTubeOrWallLine(23 + X_, 110 + Y_, 32 + X_, 110 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapMHDGenerator, LOCATION(53 + X_, 76 + Y_));

	rubbleMaker.CreateDestroyedBuilding(map_id::mapTradeCenter, LOCATION(47 + X_, 87 + Y_));

	//From Destroyed Garage to Destroyed Trade Center
	CreateTubeOrWallLine(42 + X_, 87 + Y_, 45 + X_, 87 + Y_, map_id::mapTube);

	//From Destroyed Trade Center to Destroyed Arachnid Factory
	CreateTubeOrWallLine(47 + X_, 89 + Y_, 47 + X_, 95 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapArachnidFactory, LOCATION(47 + X_, 97 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapSolarPowerArray, LOCATION(50 + X_, 39 + Y_));

	TethysGame::CreateUnit(building, map_id::mapArachnidFactory, LOCATION(53 + X_, 104 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 52);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapRobotCommand, LOCATION(53 + X_, 97 + Y_));

	//From Spaceport to Destroyed Common Ore Smelter
	CreateTubeOrWallLine(81 + X_, 22 + Y_, 81 + X_, 30 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapGuardPost, LOCATION(95 + X_, 33 + Y_));

	CreateTubeOrWallLine(95 + X_, 35 + Y_, 95 + X_, 38 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapGuardPost, LOCATION(95 + X_, 39 + Y_));

	CreateTubeOrWallLine(95 + X_, 41 + Y_, 82 + X_, 41 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapDIRT, LOCATION(69 + X_, 47 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapDIRT, LOCATION(75 + X_, 47 + Y_));

	rubbleMaker.CreateDestroyedBuilding(map_id::mapGuardPost, LOCATION(96 + X_, 67 + Y_));

	CreateTubeOrWallLine(96 + X_, 69 + Y_, 96 + X_, 73 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapGuardPost, LOCATION(96 + X_, 74 + Y_));
	rubbleMaker.CreateDestroyedBuilding(map_id::mapGuardPost, LOCATION(91 + X_, 95 + Y_));

	rubbleMaker.CreateDestroyedBuilding(map_id::mapCommandCenter, LOCATION(60 + X_, 95 + Y_));

	TethysGame::CreateWallOrTube(77 + X_, 19 + Y_, -1, map_id::mapTube);

	CreateTubeOrWallLine(55 + X_, 97 + Y_, 91 + X_, 97 + Y_, map_id::mapTube);

	rubbleMaker.CreateDestroyedBuilding(map_id::mapMHDGenerator, LOCATION(46 + X_, 120 + Y_));

	rubbleMaker.CreateDestroyedBuilding(map_id::mapStructureFactory, LOCATION(68 + X_, 63 + Y_));

	TethysGame::CreateUnit(building, map_id::mapDIRT, LOCATION(60 + X_, 89 + Y_), Player0, map_id::mapNone, 0);
	vehicleBuilder.SetPercentDamaged(building, 30);

	CreateTubeOrWallLine(60 + X_, 91 + Y_, 60 + X_, 93 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapResidence, LOCATION(67 + X_, 56 + Y_), Player0, map_id::mapNone, -1);
	vehicleBuilder.SetPercentDamaged(building, 30);

	CreateTubeOrWallLine(52 + X_, 66 + Y_, 68 + X_, 66 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(67 + X_, 58 + Y_, 67 + X_, 60 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(96 + X_, 76 + Y_, 91 + X_, 76 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(91 + X_, 76 + Y_, 91 + X_, 94 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(37 + X_, 42 + Y_, 39 + X_, 42 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapGuardPost, LOCATION(31 + X_, 58 + Y_), Player0, map_id::mapStickyfoam, -1);

	CreateTubeOrWallLine(33 + X_, 58 + Y_, 38 + X_, 58 + Y_, map_id::mapTube);
	TethysGame::CreateWallOrTube(38 + X_, 57 + Y_, -1,  map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapRareStorage, LOCATION(44 + X_, 39 + Y_), Player0, map_id::mapNone, -1);
	vehicleBuilder.SetPercentDamaged(building, 70);

	CreateTubeOrWallLine(44 + X_, 41 + Y_, 44 + X_, 42 + Y_, map_id::mapTube);

	TethysGame::CreateUnit(building, map_id::mapRareStorage, LOCATION(43 + X_, 77 + Y_), Player0, map_id::mapNone, -1);
	TethysGame::CreateUnit(building, map_id::mapCommonStorage, LOCATION(60 + X_, 102 + Y_), Player0, map_id::mapNone, -1);
	vehicleBuilder.SetPercentDamaged(building, 70);

	CreateTubeOrWallLine(60 + X_, 98 + Y_, 60 + X_, 100 + Y_, map_id::mapTube);
	CreateTubeOrWallLine(41 + X_, 79 + Y_, 43 + X_, 79 + Y_, map_id::mapTube);

	InitializeBlastedTiles(rubbleMaker);

	//vehicleBuilder.CreateVechLightsOn(building, map_id::mapConVec, LOCATION(), map_id::mapCommandCenter);
}