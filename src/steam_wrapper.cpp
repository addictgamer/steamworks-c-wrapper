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

extern "C" void* SteamGameServer()
{
	return steam::SteamGameServer();
}

extern "C" void SteamGameServer_SetModDir(const char *pszModDir)
{
	steam::SteamGameServer()->SetModDir(pszModDir);
}

extern "C" void SteamGameServer_SetProduct(const char *pszProduct)
{
	steam::SteamGameServer()->SetProduct(pszProduct);
}

extern "C" void SteamGameServer_SetGameDescription(const char *pszGameDescription)
{
	steam::SteamGameServer()->SetGameDescription(pszGameDescription);
}

extern "C" void SteamGameServer_LogOnAnonymous()
{
	steam::SteamGameServer()->LogOnAnonymous();
}

extern "C" void SteamGameServer_EnableHeartbeats(bool bActive)
{
	steam::SteamGameServer()->EnableHeartbeats(bActive);
}