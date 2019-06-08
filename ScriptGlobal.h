#pragma once

#include "Outpost2DLL/Outpost2DLL.h"

struct ScriptGlobal
{
	Trigger TrigDisaster;
	Trigger TrigFailureWaitTime;

	Trigger TrigVictoryColonists;

	Trigger TrigEscapeEvacTransports;
	Trigger TrigEscapeRoboSurveyor;
	Trigger TrigEscapeRoboDozer;
	Trigger TrigEscapeRoboMiner;
	Trigger TrigEscapeEarthworker;

	Trigger TrigEscapeScout;
	Trigger TrigEscapeSpiders;
	Trigger TrigEscapePanthers;
	Trigger TrigEscapeLynx;

	Trigger TrigEscapeCommandCenterKit;
	Trigger TrigEscapeStructureFactoryKit;
	Trigger TrigEscapeCommonSmelterKit;
	Trigger TrigEscapeTokomakKit;
	Trigger TrigEscapeAgridomeKit;
	Trigger TrigEscapeRareStorageKit;

	Trigger TrigEscapeTrucksCommonMetals;
	Trigger TrigEscapeTrucksRareMetals;
	Trigger TrigEscapeTrucksFood;

	FightGroup IdlePanthers;
	FightGroup IdleTigers;

	Trigger TrigReleaseRogueFightGroup;

	FightGroup RogueFightGroups[33];
	// Tracks if a fight group is available to task.
	bool RogueFightGroupsAvailable[33];
	int RogueFightGroupsCount = 33;

	FightGroup CommonSmelterAttackGroup;
	FightGroup StartingPatrolFightGroup;

	bool EnemyAwake = false;
	bool CommandCenterBuilt = false;
	int NumberOfHumanBuildings = 50;

	Unit ScoutCommander;
};

extern ScriptGlobal scriptGlobal;
