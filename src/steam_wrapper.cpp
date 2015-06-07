/*
 * Copyright (c) 2015 CIPRIAN ILIES
 * See LICENSE for details.
 */

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

bool SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID)
{
	return steam::SteamAPI_RestartAppIfNecessary(unOwnAppID);
}

//What is this? Where is it defined? How do I wrap it? AAAAAAAAAAAAH.
/*bool Steamworks_InitCEGLibrary()
{
	return steam::Steamworks_InitCEGLibrary();
}*/

bool SteamUser_BLoggedOn()
{
	return steam::SteamUser()->BLoggedOn();
}