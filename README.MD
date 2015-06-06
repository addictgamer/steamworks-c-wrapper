This library wraps around Valve's Steam API (Steamworks) to allow C programs to use it.

Basic instructions:

 * Get the Steamworks SDK. You should know how to do this.
 * Install the SDK in a system search path or otherwise set an environment variable pointing to it (e.g. export STEAMWORKS_ROOT="dependencies/steamworks")
The FindSTEAMWORKS.cmake module is pretty bad right now...You'll have to edit it manually for your system. I know, I don't like it either, but that's the current state of affairs.
 * Run cmake.
 * Run make
 * Run make install
The library and headers will be be in lib/ and include/