*** Plymouth Campaign Pursued - Scenario 1: Evacuation Under Fire

A new Plymouth Base Evacuation Style Campaign Scenario for Outpost 2 programmed by Vagabond in Mar of 2016. 
This is the first map of the Pursued campaign. 

*** Compatibility Notes

The scenario is compatible with Windows and WINE, although I only test scenarios on Windows before releasing.

*** Install Directions

 * Ensure Microsoft Visual C++ 2015 Redistributable (x86) is installed. It should be about a 20MB download 
   and can be found at: https://www.microsoft.com/en-us/download/details.aspx?id=48145.
 * Place the .map, .dll, and research tree (other .txt file) in your root Outpost 2 install directory. 
   Some scenarios share maps (.map) and research trees (.txt). You should not need to install over already 
   downloaded versions of maps and tech trees unless the map or tech tree is being patched for all scenarios
   using it.
 * Open Outpost 2 and search for the new scenario with the other colony games.
 * Good luck, and have fun!

*** Source Code

This scenario was built using C++ in Visual Studio 2015 using the Visual Studio 2015 Build Tools. 
C++11 and the C++ Standard Library are both used. If you want to load the scenario into a different IDE, 
a C++11 compliant IDE is required. Your IDE will also need support for the windows API and the Outpost 2 SDK ver 2.1.

Post Build Events: 3 post build events are remarked out (rem) to prevent them from copying 
files on another person's computer without their knowledge. Remove the rem from the 3 lines to
enable them.

If you need help troubleshooting the compiled scenario or the source code, use the OutpostUniverse forums.

** Bugs

 * Currently None...

** Credits

  * SirBomber - For making great tutorials that without I probably wouldn't have been able to learn the SDK.
  * Hooman - For providing technical help, especially for re-creating the Plymouth Starship II colony game. 
    This provided a lot of insight on using the SDK. Also, for solving the victory conditions/Saving bug.