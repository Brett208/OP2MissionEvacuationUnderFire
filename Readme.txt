*** Plymouth Campaign Pursued - Scenario 1: Evacuation Under Fire

A custom Plymouth Base Evacuation campaign mission for Outpost 2 programmed by Vagabond in Mar of 2016. 
This is the first mission of the Pursued Campaign and can be found in the colony games section of Outpost 2. 

*** Compatibility Notes

The scenario is compatible with Windows and WINE, although I only test scenarios on Windows before releasing.

*** Install Directions

 * Place the .map, .dll, and research tree (other .txt file) in your root Outpost 2 install directory. 
   Some scenarios share maps (.map) and research trees (.txt). You should not need to install over already 
   downloaded versions of maps and tech trees unless the map or tech tree is being patched for all scenarios
   using it.
 * Open Outpost 2 and search for the new scenario with the other colony games.
 * Good luck, and have fun!

*** Source Code

This scenario was built using C++ in Visual Studio using C++11 language features.

A post build event uses an environment variable to locate your copy of Outpost 2 and copy the dll for testing.

If you need help troubleshooting the compiled scenario or the source code, use the OutpostUniverse forums.

** Bugs

 * If you save and then load the mission before emptying vehicles in the garage, sometimes attempting to release a vehicle from the garage will crash the game. Unknown if bug is in mission logic or game logic.

** Credits

  * SirBomber - For making great tutorials that without I probably wouldn't have been able to learn the SDK.
  * Hooman - For providing technical help, especially for re-creating the Plymouth Starship II colony game. 
    This provided a lot of insight on using the SDK. Also, for solving the victory conditions/Saving bug.

** Change Log

Version 1.0.1
 - Move HFLInit from LevelInit to DLLMain, allowing initialization when loading a saved game
