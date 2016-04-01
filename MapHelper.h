#pragma once

#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

namespace MapHelper
{
	// Sets all tiles in a rectangle area to lava-possible
	void SetLavaPossibleRegion(const MAP_RECT &mapRect);

	// Sets all S1 and S2 Celltypes in a rectangle area to lava-possible 
	void SetLavaPossibleAllSlowCells(MAP_RECT mapRect);

	// Start volcano animation towards the South East
	void SetSouthEastLavaFlowAni(LOCATION location);

	// Note: Does not perform error checking to ensure fumarole isn't placed in an inapropriate area.
	void CreateFumaroleInRegion(MAP_RECT mapRect);

	void CreateBeaconRandomYield(LOCATION loc, BeaconTypes beaconType);

	LOCATION CreateBeaconFromRandomLocs(const std::vector<LOCATION> &possibleLocs,
		BeaconTypes commonRareType, Yield oreBar, Variant barVariant);

	LOCATION CreateBeaconInRegion(MAP_RECT rect, BeaconTypes commonRareType, Yield oreBar, Variant barVariant);

	LOCATION CreateMagmaWellInRegion(MAP_RECT mapRect);

	// Note: Does not perform error checking to ensure fumarole isn't placed in an inapropriate area.
	void CreateFumarolesFromRandomLocs(size_t numberOfFumaroles, std::vector<LOCATION> locations);
}