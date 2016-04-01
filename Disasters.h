#pragma once

#include "OP2Helper\OP2Helper.h"
#include "HFL\Source\HFL.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <cmath>
#include <vector>

double DistanceBetweenPoints(LOCATION loc1, LOCATION loc2);
LOCATION getRandMapLoc();
void CreateRandomDisaster(const std::vector<LOCATION> &criticalBuildingLocations);