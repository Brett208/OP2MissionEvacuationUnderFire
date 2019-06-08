#pragma once

#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

namespace MapHelper
{
	// Note: Does not perform error checking to ensure fumarole isn't placed in an inapropriate area.
	void CreateFumaroleInRegion(const MAP_RECT &mapRect);

	void CreateBeaconRandomYield(const LOCATION &loc, BeaconTypes beaconType);

	LOCATION CreateBeaconFromRandomLocs(const std::vector<LOCATION> &possibleLocs,
		BeaconTypes commonRareType, Yield oreBar, Variant barVariant);

	LOCATION CreateBeaconInRegion(const MAP_RECT &rect, BeaconTypes commonRareType, Yield oreBar, Variant barVariant);

	LOCATION CreateMagmaWellInRegion(const MAP_RECT &mapRect);

	// Note: Does not perform error checking to ensure fumarole isn't placed in an inapropriate area.
	void CreateFumarolesFromRandomLocs(size_t numberOfFumaroles, std::vector<LOCATION> locations);
}
