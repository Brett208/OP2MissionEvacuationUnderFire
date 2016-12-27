#include "MapHelper.h"

namespace MapHelper
{
	void CreateBeaconRandomYield(const LOCATION &loc, BeaconTypes beaconType)
	{
		TethysGame::CreateBeacon(map_id::mapMiningBeacon, loc.x, loc.y, beaconType, Yield::BarRandom, Variant::VariantRandom);
	}

	LOCATION CreateBeaconInRegion(const MAP_RECT &rect, BeaconTypes commonRareType, Yield oreBar, Variant barVariant)
	{
		LOCATION loc = rect.RandPt();
		TethysGame::CreateBeacon(map_id::mapMiningBeacon, loc.x, loc.y, commonRareType, oreBar, barVariant);

		return loc;
	}

	LOCATION CreateBeaconFromRandomLocs(const std::vector<LOCATION> &possibleLocs,
		BeaconTypes commonRareType, Yield oreBar, Variant barVariant)
	{
		LOCATION loc = possibleLocs[TethysGame::GetRand(possibleLocs.size())];

		TethysGame::CreateBeacon(map_id::mapMiningBeacon, loc.x, loc.y,
			commonRareType, oreBar, barVariant);

		return loc;
	}

	LOCATION CreateMagmaWellInRegion(const MAP_RECT &mapRect)
	{
		LOCATION loc = mapRect.RandPt();
		TethysGame::CreateBeacon(map_id::mapMagmaVent, loc.x, loc.y, -1, -1, -1);

		return loc;
	}

	void CreateFumaroleInRegion(const MAP_RECT &mapRect)
	{
		LOCATION fumaroleLoc = mapRect.RandPt();
		TethysGame::CreateBeacon(map_id::mapFumarole, fumaroleLoc.x, fumaroleLoc.y, -1, -1, -1);
	}

	void CreateFumarolesFromRandomLocs(size_t numberOfFumaroles, std::vector<LOCATION> locations)
	{
		if (numberOfFumaroles > locations.size())
		{
			throw "Error";
		}

		int locationIndex;
		LOCATION loc;
		for (size_t i = 0; i < numberOfFumaroles; ++i)
		{
			locationIndex = TethysGame::GetRand(locations.size());
			loc = locations[locationIndex];

			TethysGame::CreateBeacon(map_id::mapFumarole, loc.x, loc.y, -1, -1, -1);

			//NOTE: Would be more efficient removing objects from the middle of a list than a vector.
			locations.erase(locations.begin() + locationIndex);
		}
	}
}