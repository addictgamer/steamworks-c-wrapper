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

extern "C" bool SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, EServerMode eServerMode, const char* pchVersionString)
{
	return steam::SteamGameServer_Init(unIP, usSteamPort, usGamePort, usQueryPort, static_cast<steam::EServerMode>(eServerMode), pchVersionString);
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

extern "C" void SteamGameServer_LogOff()
{
	steam::SteamGameServer()->LogOff();
}

extern "C" void SteamGameServerNetworking_AcceptP2PSessionWithUser(void* steamIDRemote)
{
	steam::SteamGameServerNetworking()->AcceptP2PSessionWithUser(*static_cast<steam::CSteamID* >(steamIDRemote));
}

extern "C" bool SteamGameServerNetworking_SendP2PPacket(void* steamIDRemote, const void *pubData, uint32_t cubData, EP2PSend eP2PSendType, int nChannel)
{
	steam::SteamGameServerNetworking()->SendP2PPacket(*static_cast<steam::CSteamID* >(steamIDRemote), pubData, cubData, static_cast<steam::EP2PSend>(eP2PSendType), nChannel);
}

extern "C" EBeginAuthSessionResult SteamGameServer_BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, void* steamID)
{
	return static_cast<EBeginAuthSessionResult>(steam::SteamGameServer()->BeginAuthSession(pAuthTicket, cbAuthTicket, *static_cast<steam::CSteamID* >(steamID)));
}

extern "C" void SteamGameServer_EndAuthSession(void* steamID)
{
	steam::SteamGameServer()->EndAuthSession(*static_cast<steam::CSteamID* >(steamID));
}

extern "C" bool SteamGameServerNetworking_IsP2PPacketAvailable(uint32_t *pcubMsgSize, int nChannel)
{
	return steam::SteamGameServerNetworking()->IsP2PPacketAvailable(pcubMsgSize, nChannel);
}

extern "C" bool SteamGameServerNetworking_ReadP2PPacket(void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize, void* psteamIDRemote, int nChannel)
{
	return steam::SteamGameServerNetworking()->ReadP2PPacket(pubDest, cubDest, pcubMsgSize, static_cast<steam::CSteamID* >(psteamIDRemote), nChannel);
}

extern "C" uint64_t SteamGameServer_GetSteamID_ConvertToUInt64()
{
	return steam::SteamGameServer()->GetSteamID().ConvertToUint64();
}

extern "C" bool SteamGameServer_BSecure()
{
	return steam::SteamGameServer()->BSecure();
}

extern "C" void SteamGameServer_SendUserDisconnect(void* steamIDUser)
{
	steam::SteamGameServer()->SendUserDisconnect(*static_cast<steam::CSteamID *>(steamIDUser));
}

extern "C" void SteamGameServer_RunCallbacks()
{
	steam::SteamGameServer_RunCallbacks();
}

extern "C" void SteamGameServer_SetMaxPlayerCount(int cPlayersMax)
{
	steam::SteamGameServer()->SetMaxPlayerCount(cPlayersMax);
}

extern "C" void SteamGameServer_SetPasswordProtected(bool bPasswordProtected)
{
	steam::SteamGameServer()->SetPasswordProtected(bPasswordProtected);
}

extern "C" void SteamGameServer_SetServerName(const char *pszServerName)
{
	steam::SteamGameServer()->SetServerName(pszServerName);
}

extern "C" void SteamGameServer_SetBotPlayerCount(int cBotplayers)
{
	steam::SteamGameServer()->SetBotPlayerCount(cBotplayers);
}

extern "C" void SteamGameServer_SetMapName(const char *pszMapName)
{
	steam::SteamGameServer()->SetMapName(pszMapName);
}

extern "C" bool SteamGameServer_BUpdateUserData(void* steamIDUser, const char *pchPlayerName, uint32_t uScore)
{
	steam::SteamGameServer()->BUpdateUserData(*static_cast<steam::CSteamID* >(steamIDUser), pchPlayerName, uScore);
}