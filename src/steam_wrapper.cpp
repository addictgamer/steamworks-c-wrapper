/*
 * Copyright (c) 2015 CIPRIAN ILIES
 * See LICENSE for details.
 */

#include <string>

extern "C"
{
	#include "steam_wrapper.h"
	#undef STEAM_CALLBACK //This is defined for the C code.
}

#include <steam/steam_api.h>
#include <steam/steam_gameserver.h>

extern "C" bool c_SteamAPI_Init()
{
	return SteamAPI_Init();
}

extern "C" void c_SteamAPI_Shutdown()
{
	SteamAPI_Shutdown();
}

extern "C" bool c_SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID)
{
	return SteamAPI_RestartAppIfNecessary(unOwnAppID);
}

//What is this? Where is it defined? How do I wrap it? AAAAAAAAAAAAH.
/*bool Steamworks_InitCEGLibrary()
{
	return Steamworks_InitCEGLibrary();
}*/

extern "C" bool c_SteamUser_BLoggedOn()
{
	return SteamUser()->BLoggedOn();
}

extern "C" void c_SteamAPI_RunCallbacks()
{
	return SteamAPI_RunCallbacks();
}

extern "C" bool c_SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, c_EServerMode eServerMode, const char* pchVersionString)
{
	return SteamGameServer_Init(unIP, usSteamPort, usGamePort, usQueryPort, static_cast<EServerMode>(eServerMode), pchVersionString);
}

extern "C" void c_SteamGameServer_Shutdown()
{
	SteamGameServer_Shutdown();
}

extern "C" void* c_SteamGameServer()
{
	return SteamGameServer();
}

extern "C" void c_SteamGameServer_SetModDir(const char *pszModDir)
{
	SteamGameServer()->SetModDir(pszModDir);
}

extern "C" void c_SteamGameServer_SetProduct(const char *pszProduct)
{
	SteamGameServer()->SetProduct(pszProduct);
}

extern "C" void c_SteamGameServer_SetGameDescription(const char *pszGameDescription)
{
	SteamGameServer()->SetGameDescription(pszGameDescription);
}

extern "C" void c_SteamGameServer_LogOnAnonymous()
{
	SteamGameServer()->LogOnAnonymous();
}

extern "C" void c_SteamGameServer_EnableHeartbeats(bool bActive)
{
	SteamGameServer()->EnableHeartbeats(bActive);
}

extern "C" void c_SteamGameServer_LogOff()
{
	SteamGameServer()->LogOff();
}

extern "C" void c_SteamGameServerNetworking_AcceptP2PSessionWithUser(void* steamIDRemote)
{
	SteamGameServerNetworking()->AcceptP2PSessionWithUser(*static_cast<CSteamID* >(steamIDRemote));
}

extern "C" bool c_SteamGameServerNetworking_SendP2PPacket(void* steamIDRemote, const void *pubData, uint32_t cubData, c_EP2PSend eP2PSendType, int nChannel)
{
	return SteamGameServerNetworking()->SendP2PPacket(*static_cast<CSteamID* >(steamIDRemote), pubData, cubData, static_cast<EP2PSend>(eP2PSendType), nChannel);
}

extern "C" c_EBeginAuthSessionResult c_SteamGameServer_BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, void* steamID)
{
	return static_cast<c_EBeginAuthSessionResult>(SteamGameServer()->BeginAuthSession(pAuthTicket, cbAuthTicket, *static_cast<CSteamID* >(steamID)));
}

extern "C" void c_SteamGameServer_EndAuthSession(void* steamID)
{
	SteamGameServer()->EndAuthSession(*static_cast<CSteamID* >(steamID));
}

extern "C" bool c_SteamGameServerNetworking_IsP2PPacketAvailable(uint32_t *pcubMsgSize, int nChannel)
{
	return SteamGameServerNetworking()->IsP2PPacketAvailable(pcubMsgSize, nChannel);
}

extern "C" bool c_SteamGameServerNetworking_ReadP2PPacket(void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize, void* psteamIDRemote, int nChannel)
{
	return SteamGameServerNetworking()->ReadP2PPacket(pubDest, cubDest, pcubMsgSize, static_cast<CSteamID* >(psteamIDRemote), nChannel);
}

extern "C" uint64_t c_SteamGameServer_GetSteamID_ConvertToUInt64()
{
	return SteamGameServer()->GetSteamID().ConvertToUint64();
}

extern "C" bool c_SteamGameServer_BSecure()
{
	return SteamGameServer()->BSecure();
}

extern "C" void c_SteamGameServer_SendUserDisconnect(void* steamIDUser)
{
	SteamGameServer()->SendUserDisconnect(*static_cast<CSteamID *>(steamIDUser));
}

extern "C" void c_SteamGameServer_RunCallbacks()
{
	SteamGameServer_RunCallbacks();
}

extern "C" void c_SteamGameServer_SetMaxPlayerCount(int cPlayersMax)
{
	SteamGameServer()->SetMaxPlayerCount(cPlayersMax);
}

extern "C" void c_SteamGameServer_SetPasswordProtected(bool bPasswordProtected)
{
	SteamGameServer()->SetPasswordProtected(bPasswordProtected);
}

extern "C" void c_SteamGameServer_SetServerName(const char *pszServerName)
{
	SteamGameServer()->SetServerName(pszServerName);
}

extern "C" void c_SteamGameServer_SetBotPlayerCount(int cBotplayers)
{
	SteamGameServer()->SetBotPlayerCount(cBotplayers);
}

extern "C" void c_SteamGameServer_SetMapName(const char *pszMapName)
{
	SteamGameServer()->SetMapName(pszMapName);
}

extern "C" bool c_SteamGameServer_BUpdateUserData(void* steamIDUser, const char *pchPlayerName, uint32_t uScore)
{
	return SteamGameServer()->BUpdateUserData(*static_cast<CSteamID* >(steamIDUser), pchPlayerName, uScore);
}

extern "C" int64_t c_SteamUtils_GetAppID()
{
	return SteamUtils()->GetAppID();
}

extern "C" bool c_SteamUser()
{
	if (SteamUser())
	{
		return true;
	}
	return false;
}

extern "C" void* c_SteamUser_GetSteamID()
{
	CSteamID *id = new CSteamID();
	*id = SteamUser()->GetSteamID();
	return id; //Still don't like this method.
}

extern "C" bool c_SteamUserStats()
{
	if (SteamUserStats())
	{
		return true;
	}
	return false;
}

extern "C" bool c_SteamUserStats_RequestCurrentStats()
{
	return SteamUserStats()->RequestCurrentStats();
}

extern "C" bool c_SteamUserStats_SetAchievement(const char *pchName)
{
	return SteamUserStats()->SetAchievement(pchName);
}

extern "C" int c_SteamUserStats_GetAchievementIcon(const char *pchName)
{
	return SteamUserStats()->GetAchievementIcon(pchName);
}

extern "C" bool c_SteamUserStats_SetStat(const char *pchName, int32_t nData)
{
	return SteamUserStats()->SetStat(pchName, nData);
}

extern "C" bool c_SteamUserStats_UpdateAvgRateStat(const char *pchName, float flCountThisSession, double dSessionLength)
{
	return SteamUserStats()->UpdateAvgRateStat(pchName, flCountThisSession, dSessionLength);
}

extern "C" bool c_SteamUserStats_GetStat_Int(const char *pchName, int32_t *pData)
{
	return SteamUserStats()->GetStat(pchName, pData);
}

extern "C" bool c_SteamUserStats_GetStat_Float(const char *pchName, float *pData)
{
	return SteamUserStats()->GetStat(pchName, pData);
}

extern "C" bool c_SteamUserStats_StoreStats()
{
	return SteamUserStats()->StoreStats();
}

extern "C" const char* c_SteamUserStats_GetAchievementDisplayAttribute(const char *pchName, const char *pchKey)
{
	return SteamUserStats()->GetAchievementDisplayAttribute(pchName, pchKey);
}

extern "C" bool c_CSteamID_IsValid(void *CSteamID_instance)
{
	return static_cast<CSteamID*>(CSteamID_instance)->IsValid();
}

extern "C" int c_SteamMatchmaking_GetNumLobbyMembers(void *steamIDLobby)
{
	return SteamMatchmaking()->GetNumLobbyMembers(*static_cast<CSteamID*>(steamIDLobby)); //This looks ugly. Will it work?
}

extern "C" void* c_SteamMatchmaking_GetLobbyMemberByIndex(void *steamIDLobby, int iMember)
{
	//CSteamID id = SteamMatchmaking()->GetLobbyMemberByIndex(*static_cast<CSteamID*>(steamIDLobby), iMember);
	//return static_cast<void*>(&id);
	CSteamID *id = new CSteamID();
	*id = SteamMatchmaking()->GetLobbyMemberByIndex(*static_cast<CSteamID*>(steamIDLobby), iMember);
	return id; //Still don't like this method.
}

extern "C" const char* c_SteamFriends_GetFriendPersonaName(void *steamIDLobbyMember)
{
	return SteamFriends()->GetFriendPersonaName(*static_cast<CSteamID*>(steamIDLobbyMember));
}

extern "C" const char* c_SteamMatchmaking_GetLobbyMemberData(void *steamIDLobby, void *steamIDUser, const char *pchKey)
{
	return SteamMatchmaking()->GetLobbyMemberData(*static_cast<CSteamID*>(steamIDLobby), *static_cast<CSteamID*>(steamIDUser), pchKey);
}

extern "C" void* c_SteamMatchmaking_GetLobbyOwner(void *steamIDLobby)
{
	CSteamID *id = new CSteamID();
	*id = SteamMatchmaking()->GetLobbyOwner(*static_cast<CSteamID*>(steamIDLobby));
	return id; //Still don't like this method.
}

extern "C" bool c_SteamFriends_IsUserInSource(void *steamIDUser, void *steamIDSource)
{
	return SteamFriends()->IsUserInSource(*static_cast<CSteamID*>(steamIDUser), *static_cast<CSteamID*>(steamIDSource));
}

extern "C" c_SteamAPICall_t c_SteamMatchmaking_RequestLobbyList()
{
	return SteamMatchmaking()->RequestLobbyList();
}