/*
 * Copyright (c) 2015 CIPRIAN ILIES
 * See LICENSE for details.
 */

namespace steam
{
	#include <steam/steam_api.h>
	#include <steam/steam_gameserver.h>
}

extern "C"
{
	#include "steam_wrapper.h"
}

extern "C" bool SteamAPI_Init()
{
	return steam::SteamAPI_Init();
}

extern "C" void SteamAPI_Shutdown()
{
	steam::SteamAPI_Shutdown();
}

extern "C" bool SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID)
{
	return steam::SteamAPI_RestartAppIfNecessary(unOwnAppID);
}

//What is this? Where is it defined? How do I wrap it? AAAAAAAAAAAAH.
/*bool Steamworks_InitCEGLibrary()
{
	return steam::Steamworks_InitCEGLibrary();
}*/

extern "C" bool SteamUser_BLoggedOn()
{
	return steam::SteamUser()->BLoggedOn();
}

//Helper function to SteamGameServer_Init.
steam::EServerMode convertToSteamEServerMode(EServerMode input)
{
	steam::EServerMode result;
	result = static_cast<steam::EServerMode>(input);
	return result;
}

extern "C" bool SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, EServerMode eServerMode, const char* pchVersionString)
{
	return steam::SteamGameServer_Init(unIP, usSteamPort, usGamePort, usQueryPort, convertToSteamEServerMode(eServerMode), pchVersionString);
}

extern "C" void SteamGameServer_Shutdown()
{
	steam::SteamGameServer_Shutdown();
}