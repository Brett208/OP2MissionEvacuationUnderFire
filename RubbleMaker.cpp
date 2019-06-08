#include "RubbleMaker.h"

bool RubbleMaker::RubbleAllowed(const LOCATION &loc)
{
	int currentCellType = GameMap::GetCellType(loc);

	return
		currentCellType == CellTypes::cellDozedArea ||
		currentCellType == CellTypes::cellFastPassible1 ||
		currentCellType == CellTypes::cellFastPassible2 ||
		currentCellType == CellTypes::cellMediumPassible1 ||
		currentCellType == CellTypes::cellMediumPassible2 ||
		currentCellType == CellTypes::cellSlowPassible1 ||
		currentCellType == CellTypes::cellSlowPassible2;
}

bool RubbleMaker::CreateBlastedTile(const LOCATION &loc)
{
	int originalTileIndex = GameMap::GetTile(loc);

	for (TileChangeSet changeSet : TileIndices.BlastSets)
	{
		if (changeSet.IsTileReplaceable(originalTileIndex))
		{
			GameMap::SetTile(loc, changeSet.ReplacementTileID(TethysGame::GetRand(changeSet.ReplacementTileRange())));
			return true;
		}
	}

	return false;
}

void RubbleMaker::CreateBlastedTiles(const std::vector<LOCATION> &locs)
{
	for (const LOCATION &loc : locs)
	{
		CreateBlastedTile(loc);
	}
}

void RubbleMaker::CreateBlastedTiles(const MAP_RECT &mapRect, int count)
{
	std::vector<LOCATION> possibleBlastLocs;
	GetAllLocationsFromRect(possibleBlastLocs, mapRect);

	int placedBlastCount = 0;
	while (placedBlastCount < count)
	{
		if (possibleBlastLocs.size() == 0)
		{
			break;
		}

		int locIndex = TethysGame::GetRand(possibleBlastLocs.size());

		if (CreateBlastedTile(possibleBlastLocs[locIndex]))
		{
			++placedBlastCount;
		}

		possibleBlastLocs.erase(possibleBlastLocs.begin() + locIndex);
	}
}

bool RubbleMaker::CreateCommonRubble(const LOCATION &loc)
{
	if (!RubbleAllowed(loc))
	{
		return false;
	}

	GameMap::SetCellType(loc, CellTypes::cellRubble);

	int originalTileIndex = GameMap::GetTile(loc);

	for (TileChangeSet changeSet : TileIndices.CommonRubbleSets)
	{
		if (changeSet.IsTileReplaceable(originalTileIndex))
		{
			GameMap::SetTile(loc, changeSet.ReplacementTileID(TethysGame::GetRand(changeSet.ReplacementTileRange())));
			return true;
		}
	}

	return false;
}

bool RubbleMaker::CreateRareRubble(const LOCATION &loc)
{
	if (!RubbleAllowed(loc))
	{
		return false;
	}

	GameMap::SetCellType(loc, CellTypes::cellRubble);

	int originalTileIndex = GameMap::GetTile(loc);

	for (TileChangeSet changeSet : TileIndices.RareRubbleSets)
	{
		if (changeSet.IsTileReplaceable(originalTileIndex))
		{
			GameMap::SetTile(loc, changeSet.ReplacementTileID(TethysGame::GetRand(changeSet.ReplacementTileRange())));
			return true;
		}
	}

	return false;
}

void RubbleMaker::CreateRandomRubble(const MAP_RECT &mapRect, int commonRubbleAmount, int rareRubbleAmount)
{
	std::vector<LOCATION> possRubbleLocs;
	GetAllLocationsFromRect(possRubbleLocs, mapRect);

	CreateRandomCommonRubble(commonRubbleAmount, possRubbleLocs);
	CreateRandomRareRubble(rareRubbleAmount, possRubbleLocs);
}

void RubbleMaker::CreateDestroyedBuilding(const LOCATION &loc, int buildingWidth, int buildingHeight,
	bool includeTubes, int commonRubbleAmount, int rareRubbleAmount)
{
	MAP_RECT buildingDozedRect = GetBuildingDozedRect(loc, buildingWidth, buildingHeight);
	MAP_RECT buildingFootprint = GetBuildingFootprint(buildingDozedRect);

	Doze(buildingDozedRect);

	if (includeTubes)
	{
		CreateDestroyedBuildingTubes(loc, buildingDozedRect);
	}

	CreateRandomRubble(buildingFootprint, commonRubbleAmount, rareRubbleAmount);
}

void RubbleMaker::CreateDestroyedBuilding(map_id buildingType, const LOCATION &loc)
{
	UnitInfo unitInfo = UnitInfo(buildingType);

	bool includeTubes = true;
	int commonRubbleCount = 1;
	int rareRubbleCount = 0;

	switch (buildingType)
	{
	case map_id::mapLightTower:
		includeTubes = false;
		commonRubbleCount = 0;
		break;
	case map_id::mapResidence:
	case map_id::mapCommonStorage:
	case map_id::mapRareStorage:
	case map_id::mapAgridome:
	case map_id::mapRecreationFacility:
	case map_id::mapNursery:
	case map_id::mapGuardPost:
	case map_id::mapForum:
		break;
	case map_id::mapCommonOreMine:
	case map_id::mapRareOreMine:
	case map_id::mapMagmaWell:
		includeTubes = false;
		break;
	case map_id::mapSolarPowerArray:
		includeTubes = false;
		commonRubbleCount = 1;
		rareRubbleCount = 1;
	case map_id::mapUniversity:
	case map_id::mapGORF:
	case map_id::mapTradeCenter:
	case map_id::mapAdvancedResidence:
	case map_id::mapReinforcedResidence:
		commonRubbleCount = 2;
		break;
	case map_id::mapGeothermalPlant:
		commonRubbleCount = 2;
		includeTubes = false;
	case map_id::mapMHDGenerator:
		includeTubes = false;
		commonRubbleCount = 2;
		rareRubbleCount = 1;
		break;
	case map_id::mapTokamak:
		includeTubes = false;
		commonRubbleCount = 3;
		break;
	case map_id::mapArachnidFactory:
	case map_id::mapGarage:
	case map_id::mapBasicLab:
	case map_id::mapStandardLab:
	case map_id::mapRobotCommand:
	case map_id::mapConsumerFactory:
	case map_id::mapDIRT:
		commonRubbleCount = 3;
		break;
	case map_id::mapObservatory:
	case map_id::mapMeteorDefense:
		commonRubbleCount = 3;
		rareRubbleCount = 1;
		break;
	case map_id::mapAdvancedLab:
		commonRubbleCount = 4;
		break;
	case map_id::mapVehicleFactory:
	case map_id::mapCommonOreSmelter:
		commonRubbleCount = 5;
		break;
	case map_id::mapCommandCenter:
	case map_id::mapStructureFactory:
	case map_id::mapRareOreSmelter:
		commonRubbleCount = 6;
		break;
	case map_id::mapSpaceport:
		commonRubbleCount = 7;
		rareRubbleCount = 1;
		break;
	}

	//A bug in HFL makes unitInfo.GetRubble() and unitInfo.GetRareRubble() return the wrong value.
	//CreateDestroyedBuilding(loc, unitInfo.GetXSize(), unitInfo.GetYSize(), includeTubes, unitInfo.GetRubble(), unitInfo.GetRareRubble());
	CreateDestroyedBuilding(loc, unitInfo.GetXSize(), unitInfo.GetYSize(), includeTubes, commonRubbleCount, rareRubbleCount);
}

// PRIVATE FUNCTIONS

void RubbleMaker::GetAllLocationsFromRect(std::vector<LOCATION> &locations, const MAP_RECT &mapRect)
{
	for (int y = 0; y < mapRect.Height(); ++y)
	{
		for (int x = 0; x < mapRect.Width(); ++x)
		{
			locations.push_back(LOCATION(mapRect.x1 + x, mapRect.y1 + y));
		}
	}
}

MAP_RECT RubbleMaker::GetBuildingDozedRect(const LOCATION &buildingLoc, int buildingWidth, int buildingHeight)
{
	LOCATION topLeftDozedTile(
		buildingLoc.x - buildingWidth / 2,
		buildingLoc.y - buildingHeight / 2);

	LOCATION bottomRightOfFootprint(topLeftDozedTile.x + buildingWidth, topLeftDozedTile.y + buildingHeight);

	return MAP_RECT(LOCATION(topLeftDozedTile.x - 1, topLeftDozedTile.y - 1), bottomRightOfFootprint);
}

MAP_RECT RubbleMaker::GetBuildingFootprint(const MAP_RECT &buildingFootprint)
{
	return MAP_RECT(
		buildingFootprint.x1 + 1,
		buildingFootprint.y1 + 1,
		buildingFootprint.x2 - 1,
		buildingFootprint.y2 - 1);
}

// Removes LOCATIONS from possRubbleLocs where rubble is now added.
void RubbleMaker::CreateRandomCommonRubble(int commonRubbleAmount, std::vector<LOCATION> &possRubbleLocs)
{
	for (int i = 0; i < commonRubbleAmount; ++i)
	{
		if (possRubbleLocs.size() == 0)
		{
			return;
		}

		int rubbleLocIndex = TethysGame::GetRand(possRubbleLocs.size());
		LOCATION rubbleLoc = possRubbleLocs[rubbleLocIndex];

		CreateCommonRubble(rubbleLoc);

		possRubbleLocs.erase(possRubbleLocs.begin() + rubbleLocIndex);
	}
}

// Removes LOCATIONS from possRubbleLocs where rubble is now added.
void RubbleMaker::CreateRandomRareRubble(int rareRubbleAmount, std::vector<LOCATION> &possRubbleLocs)
{
	for (int i = 0; i < rareRubbleAmount; ++i)
	{
		if (possRubbleLocs.size() == 0)
		{
			return;
		}

		int rubbleLocIndex = TethysGame::GetRand(possRubbleLocs.size());
		LOCATION rubbleLoc = possRubbleLocs[rubbleLocIndex];

		CreateRareRubble(rubbleLoc);

		possRubbleLocs.erase(possRubbleLocs.begin() + rubbleLocIndex);
	}
}

void RubbleMaker::CreateDestroyedBuildingTubes(const LOCATION &buildingLoc, const MAP_RECT &buildingFootprint)
{
	LOCATION southTubeLoc(buildingLoc.x, buildingFootprint.y2);
	LOCATION eastTubeLoc(buildingFootprint.x2, buildingLoc.y);

	if (RubbleAllowed(southTubeLoc))
	{
		// The tile's celltype North of the Southern tube is temporarily set to tube to ensure the tube is orientied North/South.
		LOCATION fauxTubeCellLoc(southTubeLoc.x, southTubeLoc.y - 1);
		CellTypes fauxTubeCellOriginalType = (CellTypes)GameMap::GetCellType(fauxTubeCellLoc);

		GameMap::SetCellType(fauxTubeCellLoc, CellTypes::cellTube0);
		TethysGame::CreateWallOrTube(southTubeLoc.x, southTubeLoc.y, -1, map_id::mapTube);

		GameMap::SetCellType(fauxTubeCellLoc, fauxTubeCellOriginalType);
	}

	if (RubbleAllowed(eastTubeLoc))
	{
		TethysGame::CreateWallOrTube(eastTubeLoc.x, eastTubeLoc.y, -1, map_id::mapTube);
	}
}

//In case of eliminating HFL
//struct BuildingInfo
//{
//	bool IncludesTubes;
//	int CommonRubbleCount;
//	int RareRubbleCount;
//	int FootprintWidth;
//	int FootprintHeight;
//};
//
//std::map<map_id, BuildingInfo> BuildingInfoMap;
