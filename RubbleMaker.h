#pragma once

#include "OP2Helper\Bulldozer.h"
#include "HFL\Source\HFL.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>
 
class TileGroup;
class TileSubSet;
class TileChangeSet;
class TileIndices;

// Inclusive group of consectutive tiles defined by mapping ID.
class TileGroup
{
public:
	TileGroup() {}

	TileGroup(int firstIndex, int lastIndex)
	{
		FirstIndex = firstIndex;
		LastIndex = lastIndex;
	}

	bool ContainsTile(int tileIndex)
	{
		return tileIndex >= FirstIndex && tileIndex <= LastIndex;
	};

	int Range()
	{
		return LastIndex - FirstIndex + 1;
	};

	int GetTile(int range)
	{
		return FirstIndex + range;
	};

private:
	int FirstIndex;
	int LastIndex;
};

// One or more TileGroups that should be treated the same.
class TileSubSet
{
public:
	TileSubSet() {}

	TileSubSet(char* name, int firstIndex, int lastIndex)
	{
		Name = name;

		TileGroups.push_back(TileGroup(firstIndex, lastIndex));
	}

	TileSubSet(char* name, int numbGroups, ...)
	{
		Name = name;

		va_list tileGroups;

		va_start(tileGroups, numbGroups);
		for (int i = 0; i < numbGroups; i++)
		{
			TileGroups.push_back(va_arg(tileGroups, TileGroup));
		}
		va_end(tileGroups);
	}

	char* GetName() { return Name; };

	// Returns if any of the member TileGroups contains the TileID
	bool ContainsTile(int tileID)
	{
		for (TileGroup tileGroup : TileGroups)
		{
			if (tileGroup.ContainsTile(tileID))
			{
				return true;
			}
		}

		return false;
	}

	// The total number of tiles included in all member TileGroups.
	int Range()
	{
		int range = 0;

		for (TileGroup tileGroup : TileGroups)
		{
			range += tileGroup.Range();
		}

		return range;
	};

// Returns a TileID based on the combined range of all member TileGroups.
	int GetTile(int range)
	{
		int tileID = 0;

		for (TileGroup tileGroup : TileGroups)
		{
			if (tileGroup.Range() < range)
			{
				range -= tileGroup.Range();
			}
			else
			{
				return tileGroup.GetTile(range);
			}
		}

		return -1;
	};

private:
	char* Name;
	std::vector<TileGroup> TileGroups;
};

// Includes 2 TileGroups. A Replaceable TileGroup that indicates which tiles may be replaced and a 
// Replacement TileGroup that indicates which tiles are valid replacement tiles.
class TileChangeSet
{
public:
	TileChangeSet() {}

	TileChangeSet(TileSubSet replacementTiles, TileSubSet replaceableTiles)
	{
		ReplacementTiles = replacementTiles;
		ReplaceableTiles = replaceableTiles;
	}

	// Returns if the replaceable TileGroup contains the tileID.
	bool IsTileReplaceable(int tileID)
	{
		return ReplaceableTiles.ContainsTile(tileID);
	};

	// Returns the total number of possible replacement tiles.
	int ReplacementTileRange()
	{
		return ReplacementTiles.Range();
	};

	// Returns a replacement tileID based on it's range in the Replacement TileGroup.
	int ReplacementTileID(int replacementRange)
	{
		return ReplacementTiles.GetTile(replacementRange);
	};

private:
	TileSubSet ReplacementTiles;
	TileSubSet ReplaceableTiles;
};

// Defines noteorthy tile groupings for editing map tiles. The default TileGroups represent the stock Outpost 2 TileSet. 
// Values may be replaced for custom tileSets.
class TileIndices
{
public:
	// Common Rubble TileGroups and TileGroups that common rubble may replace.
	std::vector<TileChangeSet> CommonRubbleSets = std::vector<TileChangeSet>{
		TileChangeSet(TileSubSet("Common Mud Rubble", 323, 326), TileSubSet("Mud Replaceable By Rubble", 0, 438)),
		TileChangeSet(TileSubSet("Common Rock Rubble", 830, 833), TileSubSet("Rock Replaceable By Rubble", 439, 1205)),
		TileChangeSet(TileSubSet("Common Sand Rubble", 1585, 1588), TileSubSet("Sand Replaceable by Rubble", 1206, 2011)) };

	// Rare Rubble TileGroups and TileGroups that rare rubble may replace.
	std::vector<TileChangeSet> RareRubbleSets = std::vector<TileChangeSet>{
		TileChangeSet(TileSubSet("Rare Mud Rubble", 327, 330), TileSubSet("Mud Replaceable By Rubble", 0, 438)),
		TileChangeSet(TileSubSet("Rare Rock Rubble", 834, 837), TileSubSet("Rock Replaceable By Rubble", 439, 1205)),
		TileChangeSet(TileSubSet("Rare Sand Rubble", 1589, 1592), TileSubSet("Sand Replaceable by Rubble", 1206, 2011)),
	};

	// Blast Mark TileGroups and TileGroups that blast marks may replace.
	std::vector<TileChangeSet> BlastSets = std::vector<TileChangeSet>
	{
		TileChangeSet(TileSubSet("Rough Mud Blasts", 267, 269), TileSubSet("Rough Mud Replaceable By Blasts", 0, 32)),
		TileChangeSet(TileSubSet("Dozed Mud Blasts", 264, 266), TileSubSet("Dozed Mud Replaceable By Blasts", 409, 416)),
		TileChangeSet(TileSubSet("Rough Rock Blasts", 792, 794), TileSubSet("Rough Rock Replaceable By Blasts", 439, 504)),
		TileChangeSet(TileSubSet("Dozed Rock Blasts", 789, 791), TileSubSet("Dozed Rock Replaceable By Blasts", 921, 928)),
		TileChangeSet(TileSubSet("Rough Sand Blasts", 1550, 1552), TileSubSet("Rough Sand Replaceable By Blasts", 2, TileGroup{ 1206, 1269 }, TileGroup{ 1286, 1295 })),
		TileChangeSet(TileSubSet("Dozed Sand Blasts", 1547, 1549), TileSubSet("Dozed Sand Replaceable By Blasts", 1670, 1677))
	};
};

/*Automates placing Rubble, Blast Marks (meteor strikes or destroyed vehicles) and Destroyed 
Buildings. When attempting to place rubble or blast marks, LOCATIONs are checked to ensure 
they are valid before placement. When placing multiple blast marks or rubble, if not enough
valid LOCATIONs are provided, the function will place as many as possible and then exit.

BLAST MARK - Will not be added to transition tiles (like mud/dirt), special objects (like 
conestoga debris tiles), or special terrain features (like multi-tile craters and cliffs).

RUBBLE - Will only be placed on tiles with a unit passable CellType.

DESTROYED BUILDING - Destroyed buildings include the properly sized extended 
dozed footprint, 2 tubes if appropriate, and proper number of common and rare rubble. No
error checking is done to ensure LOCATION of destroyed building is valid (IE no cliffs in 
the middle).*/
class RubbleMaker
{
public:
	// Default constructor used stock Outpost 2 Tile Set.
	RubbleMaker()
	{
		TileIndices = class TileIndices();
	}

	// Pass modified TileIndices class for custom Tile Sets.
	RubbleMaker(const TileIndices &tileIndices)
	{
		TileIndices = tileIndices;
	};

	// Attempts to place blasted tile. Returns true if placement successful.
	bool CreateBlastedTile(const LOCATION &loc);

	//Attempts to randomly place blasted tiles within a MAP_RECT.
	void CreateBlastedTiles(const MAP_RECT &mapRect, int count);

	//Attempts to place blasted tiles at each location.
	template<typename LOCATION, size_t N>
	void CreateBlastedTiles(const std::array<LOCATION, N> &locs)
	{
		for (const LOCATION &loc : locs)
		{
			CreateBlastedTile(loc);
		}
	}

	// Attempts to place blasted tiles at each location.
	void CreateBlastedTiles(const std::vector<LOCATION> &locs);
	
	bool RubbleAllowed(const LOCATION &loc);

	// Attempts to place common rubble. Returns true if placement successful.
	bool CreateCommonRubble(const LOCATION &loc);

	// Attempts to place rare rubble. Returns true if placement successful.
	bool CreateRareRubble(const LOCATION &loc);

	// Attempts to place rubble randomly over provided MAP_RECT.
	void CreateRandomRubble(const MAP_RECT &mapRect, int commonRubbleAmount, int rareRubbleAmount);
	
	// Places a destroyed building of given map_id type. LOCATION specifies the position 
	// where the North/South and East/West tubes would meet underneath the structure. 
	void CreateDestroyedBuilding(map_id buildingType, const LOCATION &loc);

	// Places a destroyed building with custom parameters.
	void CreateDestroyedBuilding(const LOCATION &loc, int buildingWidth, int buildingHeight, 
		bool includeTubes, int commonRubbleAmount, int rareRubbleAmount);

private:
	TileIndices TileIndices;

	void GetAllLocationsFromRect(std::vector<LOCATION> &locations, const MAP_RECT &mapRect);
	MAP_RECT GetBuildingDozedRect(const LOCATION &loc, int buildingWidth, int buildingHeight); //Returned MAP_RECT does not include dozed perimeter tiles of building. 
	MAP_RECT GetBuildingFootprint(const MAP_RECT &buildingFootprint);

	void RubbleMaker::CreateRandomCommonRubble(int commonRubbleAmount, std::vector<LOCATION> &possRubbleLocs);
	void RubbleMaker::CreateRandomRareRubble(int rareRubbleAmount, std::vector<LOCATION> &possRubbleLocs);
	void RubbleMaker::CreateDestroyedBuildingTubes(const LOCATION &buildingLoc, const MAP_RECT &buildingFootprint);
};