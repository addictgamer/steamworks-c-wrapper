namespace steam
{
	#include <steam/steam_api.h>
}

extern "C"
{
	#include "steam_wrapper.h"
}

bool SteamAPI_Init()
{
	return steam::SteamAPI_Init();
}

void SteamAPI_Shutdown()
{
	steam::SteamAPI_Shutdown();
}