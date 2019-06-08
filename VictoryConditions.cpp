#include "ScriptGlobal.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

const MAP_RECT evacuateArea(LOCATION(1 + X_, 1 + Y_), LOCATION(25 + X_, 25 + Y_));

void CreateCountVictoryTrigger(Trigger& trigger, map_id unit, map_id cargo, int minCount, char* missionObjective)
{
	trigger = CreateCountTrigger(true, false, Player0, unit, cargo, minCount, compare_mode::cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, trigger, missionObjective);
}

void CreateCountVictoryTrigger(Trigger& trigger, map_id unit, int minCount, char* missionObjective)
{
	CreateCountVictoryTrigger(trigger, unit, map_id::mapNone, minCount, missionObjective);
}

void CreateEscapeVictoryCondition(Trigger& trigger, MAP_RECT rect, int unitCount, map_id unitType, int cargoType, int cargoAmount, char* missionObjective)
{
	trigger = CreateEscapeTrigger(true, false, Player0, rect.x1, rect.y1, rect.Width(), rect.Height(), unitCount, unitType, cargoType, cargoAmount, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, trigger, missionObjective);
}

void InitializeVictoryConditions()
{
	scriptGlobal.TrigVictoryColonists = CreateResourceTrigger(true, false, trig_res::resColonists, 50, Player0, compare_mode::cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, scriptGlobal.TrigVictoryColonists, "Have 50 or more colonists.");

	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeTrucksFood, evacuateArea, 2, map_id::mapCargoTruck, (map_id)truckFood, 2000, "Stage 2,000 units of Food to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeTrucksRareMetals, evacuateArea, 1, map_id::mapCargoTruck, (map_id)truckRareMetal, 1000, "Stage 1,000 units of Rare Metals to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeTrucksCommonMetals, evacuateArea, 3, map_id::mapCargoTruck, (map_id)truckCommonMetal, 3000, "Stage 3,000 units of Common Metals to the Northwest.");

	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeEvacTransports, evacuateArea, 3, map_id::mapEvacuationTransport, map_id::mapAny, 0, "Stage 3 Evac Transports to the Nortwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeRoboDozer, evacuateArea, 1, map_id::mapRoboDozer, map_id::mapAny, 0, "Stage 1 RoboDozer to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeEarthworker, evacuateArea, 1, map_id::mapEarthworker, map_id::mapAny, 0, "Stage 1 Earthworker to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeRoboMiner, evacuateArea, 1, map_id::mapRoboMiner, map_id::mapAny, 0, "Stage 1 Robo-Miner to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeRoboSurveyor, evacuateArea, 1, map_id::mapRoboSurveyor, map_id::mapAny, 0, "Stage 1 Robo-Surveyors to the Northwest.");

	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeRareStorageKit, evacuateArea, 1, map_id::mapConVec, map_id::mapRareStorage, 1, "Stage ConVec with a Rare Metals Storage to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeAgridomeKit, evacuateArea, 1, map_id::mapConVec, map_id::mapAgridome, 1, "Stage ConVec with an Agridome to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeTokomakKit, evacuateArea, 1, map_id::mapConVec, map_id::mapTokamak, 1, "Stage ConVec with a Tokamak to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeCommonSmelterKit, evacuateArea, 1, map_id::mapConVec, map_id::mapCommonOreSmelter, 1, "Stage ConVec with a Common Ore Smelter to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeStructureFactoryKit, evacuateArea, 1, map_id::mapConVec, map_id::mapStructureFactory, 1, "Stage ConVec with a Structure Factory to the Northwest.");
	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeCommandCenterKit, evacuateArea, 1, map_id::mapConVec, map_id::mapCommandCenter, 1, "Stage ConVec with a Command Center to the Northwest.");

	if (Player[0].Difficulty() == PlayerDifficulty::DiffHard)
	{ 
		CreateEscapeVictoryCondition(scriptGlobal.TrigEscapePanthers, evacuateArea, 3, map_id::mapPanther, map_id::mapAny, 0, "Stage 3 Panthers to the Northwest.");
		CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeLynx, evacuateArea, 4, map_id::mapLynx, map_id::mapAny, 0, "Stage 4 Lynx to the Northwest.");
		CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeSpiders, evacuateArea, 2, map_id::mapSpider, map_id::mapAny, 0, "Stage 2 Spiders to the Northwest.");
	}

	CreateEscapeVictoryCondition(scriptGlobal.TrigEscapeScout, evacuateArea, 1, map_id::mapScout, map_id::mapAny, 0, "Stage 1 Scout to the Northwest.");
}
