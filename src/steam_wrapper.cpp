/*
 * Copyright (c) 2015 CIPRIAN ILIES
 * See LICENSE for details.
 */

#include <string>

#include "Config.h"

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

extern "C" void c_Free_CSteamID(void *steamID)
{
	CSteamID *id = static_cast<CSteamID*>(steamID);
	delete id;
}

extern "C" void* c_AllocateNew_CSteamID()
{
	CSteamID *id = new CSteamID();
	return id;
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

extern "C" void* c_SteamMatchmaking_GetLobbyByIndex(int iLobby)
{
	CSteamID *id = new CSteamID();
	*id = SteamMatchmaking()->GetLobbyByIndex(iLobby);
	return id;
}

extern "C" bool c_SteamMatchmaking_RequestLobbyData(void *steamIDLobby)
{
	return SteamMatchmaking()->RequestLobbyData(*static_cast<CSteamID*>(steamIDLobby));
}

//steamIDLobby.GetAccountID()
extern "C" c_AccountID_t c_CSteamID_GetAccountID(void *CSteamID_instance)
{
	return static_cast<CSteamID*>(CSteamID_instance)->GetAccountID();
}

extern "C" bool c_SteamUtils_IsAPICallCompleted(ulong hSteamAPICall, bool *pbFailed)
{
	return SteamUtils()->IsAPICallCompleted(hSteamAPICall, pbFailed);
}

extern "C" bool c_SteamUtils_GetAPICallResult(c_SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
{
	return SteamUtils()->GetAPICallResult(hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed);
}

extern "C" uint32_t c_LobbyMatchList_t_m_nLobbiesMatching(void *LobbyMatchList_t_instance)
{
	return static_cast<LobbyMatchList_t*>(LobbyMatchList_t_instance)->m_nLobbiesMatching;
}

extern "C" void c_SteamMatchmaking_AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, c_ELobbyComparison eComparisonType)
{
	SteamMatchmaking()->AddRequestLobbyListStringFilter(pchKeyToMatch, pchValueToMatch, static_cast<ELobbyComparison>(eComparisonType));
}

extern "C" void c_SteamMatchmaking_AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, c_ELobbyComparison eComparisonType)
{
	SteamMatchmaking()->AddRequestLobbyListNumericalFilter(pchKeyToMatch, nValueToMatch, static_cast<ELobbyComparison>(eComparisonType));
}

extern "C" void c_SteamMatchmaking_AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo)
{
	SteamMatchmaking()->AddRequestLobbyListNearValueFilter(pchKeyToMatch, nValueToBeCloseTo);
}

extern "C" void c_SteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable)
{
	SteamMatchmaking()->AddRequestLobbyListFilterSlotsAvailable(nSlotsAvailable);
}

extern "C" c_SteamAPICall_t c_SteamMatchmaking_CreateLobby(c_ELobbyType eLobbyType, int cMaxMembers)
{
	return SteamMatchmaking()->CreateLobby(static_cast<ELobbyType>(eLobbyType), cMaxMembers);
}

extern "C" c_SteamAPICall_t c_SteamMatchmaking_JoinLobby(void *steamIDLobby)
{
	return SteamMatchmaking()->JoinLobby(*static_cast<CSteamID*>(steamIDLobby));
}

extern "C" bool c_SteamMatchmaking_SetLobbyData(void *steamIDLobby, const char *pchKey, const char *pchValue)
{
	return SteamMatchmaking()->SetLobbyData(*static_cast<CSteamID*>(steamIDLobby), pchKey, pchValue);
}

extern "C" bool c_SteamMatchmaking_DeleteLobbyData(void *steamIDLobby, const char *pchKey)
{
	return SteamMatchmaking()->DeleteLobbyData(*static_cast<CSteamID*>(steamIDLobby), pchKey);
}

extern "C" int c_SteamMatchmaking_GetLobbyDataCount(void *steamIDLobby)
{
	return SteamMatchmaking()->GetLobbyDataCount(*static_cast<CSteamID*>(steamIDLobby));
}

extern "C" bool c_SteamMatchmaking_GetLobbyDataByIndex(void *steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize)
{
	return SteamMatchmaking()->GetLobbyDataByIndex(*static_cast<CSteamID*>(steamIDLobby), iLobbyData, pchKey, cchKeyBufferSize, pchValue, cchValueBufferSize);
}

extern "C" bool c_SteamMatchmaking_SendLobbyChatMsg(void *steamIDLobby, const void *pvMsgBody, int cubMsgBody)
{
	return SteamMatchmaking()->SendLobbyChatMsg(*static_cast<CSteamID*>(steamIDLobby), pvMsgBody, cubMsgBody);
}

extern "C" int c_SteamMatchmaking_GetLobbyChatEntry(void *steamIDLobby, int iChatID, void *pSteamIDUser, void *pvData, int cubData, c_EChatEntryType *peChatEntryType)
{
	return SteamMatchmaking()->GetLobbyChatEntry(*static_cast<CSteamID*>(steamIDLobby), iChatID, static_cast<CSteamID*>(pSteamIDUser), pvData, cubData, reinterpret_cast<EChatEntryType*>(peChatEntryType));
}

extern "C" bool c_SteamFriends_SetRichPresence(const char *pchKey, const char *pchValue)
{
	return SteamFriends()->SetRichPresence(pchKey, pchValue);
}

extern "C" int c_SteamFriends_GetFriendCount(int iFriendFlags)
{
	return SteamFriends()->GetFriendCount(iFriendFlags);
}

extern "C" bool c_SteamMatchmaking_InviteUserToLobby(void *steamIDLobby, void *steamIDInvitee)
{
	return SteamMatchmaking()->InviteUserToLobby(*static_cast<CSteamID*>(steamIDLobby), *static_cast<CSteamID*>(steamIDInvitee));
}

extern "C" void c_SteamFriends_ActivateGameOverlay(const char *pchDialog)
{
	SteamFriends()->ActivateGameOverlay(pchDialog);
}

extern "C" void c_SteamMatchmaking_LeaveLobby(void *steamIDLobby)
{
	SteamMatchmaking()->LeaveLobby(*static_cast<CSteamID*>(steamIDLobby));
}

extern "C" bool c_SteamFriends_GetFriendGamePlayed(void *steamIDFriend, void *pFriendGameInfo)
{
	return SteamFriends()->GetFriendGamePlayed(*static_cast<CSteamID*>(steamIDFriend), static_cast<FriendGameInfo_t*>(pFriendGameInfo));
}

extern "C" void* c_FriendGameInfo_t_m_steamIDLobby(void *FriendGameInfo_t_instance)
{
	CSteamID *id = new CSteamID;
	*id = static_cast<FriendGameInfo_t*>(FriendGameInfo_t_instance)->m_steamIDLobby;
	return id;
}

extern "C" void* c_P2PSessionRequest_t_m_steamIDRemote(void *P2PSessionRequest_t_instance)
{
	CSteamID *id = new CSteamID;
	*id = static_cast<P2PSessionRequest_t*>(P2PSessionRequest_t_instance)->m_steamIDRemote;
	return id;
}

class SteamServerWrapper
{
public:
	SteamServerWrapper()
	:
	m_CallbackP2PSessionRequest(this, &SteamServerWrapper::OnP2PSessionRequest),
	m_CallbackP2PSessionConnectFail(this, &SteamServerWrapper::OnP2PSessionConnectFail),
	m_SteamServersConnected(this, &SteamServerWrapper::OnSteamServersConnected),
	m_SteamServersDisconnected(this, &SteamServerWrapper::OnSteamServersDisconnected),
	m_CallbackPolicyResponse(this, &SteamServerWrapper::OnPolicyResponse),
	m_CallbackGSAuthTicketResponse(this, &SteamServerWrapper::OnValidateAuthTicketResponse)
	{
		//Stuff.
	}

	STEAM_GAMESERVER_CALLBACK(SteamServerWrapper, OnP2PSessionRequest, P2PSessionRequest_t, m_CallbackP2PSessionRequest);

	STEAM_GAMESERVER_CALLBACK(SteamServerWrapper, OnP2PSessionConnectFail, P2PSessionConnectFail_t, m_CallbackP2PSessionConnectFail);

	STEAM_GAMESERVER_CALLBACK(SteamServerWrapper, OnSteamServersConnected, SteamServersConnected_t, m_SteamServersConnected);

	STEAM_GAMESERVER_CALLBACK(SteamServerWrapper, OnSteamServersDisconnected, SteamServersDisconnected_t, m_SteamServersDisconnected);

	STEAM_GAMESERVER_CALLBACK(SteamServerWrapper, OnPolicyResponse, GSPolicyResponse_t, m_CallbackPolicyResponse);

	STEAM_GAMESERVER_CALLBACK(SteamServerWrapper, OnValidateAuthTicketResponse, ValidateAuthTicketResponse_t, m_CallbackGSAuthTicketResponse);
} *steam_server_wrapper;

void SteamServerWrapper::OnP2PSessionRequest(P2PSessionRequest_t *pCallback)
{
	if (c_SteamServerWrapper_OnP2PSessionRequest)
		(*c_SteamServerWrapper_OnP2PSessionRequest)(pCallback);
}

void SteamServerWrapper::OnP2PSessionConnectFail(P2PSessionConnectFail_t *pCallback)
{
	if (c_SteamServerWrapper_OnP2PSessionConnectFail)
		(*c_SteamServerWrapper_OnP2PSessionConnectFail)(pCallback);
}

void SteamServerWrapper::OnSteamServersConnected(SteamServersConnected_t *pLogonSuccess)
{
	if (c_SteamServerWrapper_OnSteamServersConnected)
		(*c_SteamServerWrapper_OnSteamServersConnected)(pLogonSuccess);
}

void SteamServerWrapper::OnSteamServersDisconnected(SteamServersDisconnected_t *pLoggedOff)
{
	if (c_SteamServerWrapper_OnSteamServersDisconnected)
		(*c_SteamServerWrapper_OnSteamServersDisconnected)(pLoggedOff);
}

void SteamServerWrapper::OnPolicyResponse(GSPolicyResponse_t *pPolicyResponse)
{
	if (c_SteamServerWrapper_OnPolicyResponse)
		(*c_SteamServerWrapper_OnPolicyResponse)(pPolicyResponse);
}

void SteamServerWrapper::OnValidateAuthTicketResponse(ValidateAuthTicketResponse_t *pResponse)
{
	if (c_SteamServerWrapper_OnValidateAuthTicketResponse)
		(*c_SteamServerWrapper_OnValidateAuthTicketResponse)(pResponse);
}

extern "C" void c_SteamServerWrapper_Instantiate()
{
	steam_server_wrapper = new SteamServerWrapper();
}

extern "C" void c_SteamServerWrapper_Destroy()
{
	delete steam_server_wrapper;
	steam_server_wrapper = nullptr;
}

extern "C" void* c_P2PSessionConnectFail_t_m_steamIDRemote(void *P2PSessionConnectFail_t_instance)
{
	CSteamID *id = new CSteamID;
	*id = static_cast<P2PSessionConnectFail_t*>(P2PSessionConnectFail_t_instance)->m_steamIDRemote;
	return id;
}

extern "C" c_EAuthSessionResponse c_ValidateAuthTicketResponse_t_EAuthSessionResponse(void *ValidateAuthTicketResponse_t_instance)
{
	return static_cast<c_EAuthSessionResponse>(static_cast<ValidateAuthTicketResponse_t*>(ValidateAuthTicketResponse_t_instance)->m_eAuthSessionResponse);
}

extern "C" void* c_ValidateAuthTicketResponse_t_m_SteamID(void *ValidateAuthTicketResponse_t_instance)
{
	CSteamID *id = new CSteamID;
	*id = static_cast<ValidateAuthTicketResponse_t*>(ValidateAuthTicketResponse_t_instance)->m_SteamID;
	return id;
}

class SteamServerClientWrapper
{
public:
	SteamServerClientWrapper()
	:
	m_CallbackP2PSessionConnectFail(this, &SteamServerClientWrapper::OnP2PSessionConnectFail),
	m_LobbyGameCreated(this, &SteamServerClientWrapper::OnLobbyGameCreated),
	m_IPCFailureCallback(this, &SteamServerClientWrapper::OnIPCFailure),
	m_SteamShutdownCallback(this, &SteamServerClientWrapper::OnSteamShutdown),
	m_SteamServersConnected(this, &SteamServerClientWrapper::OnSteamServersConnected),
	m_SteamServersDisconnected(this, &SteamServerClientWrapper::OnSteamServersDisconnected),
	m_SteamServerConnectFailure(this, &SteamServerClientWrapper::OnSteamServerConnectFailure),
	m_GameJoinRequested(this, &SteamServerClientWrapper::OnGameJoinRequested),
	m_CallbackGameOverlayActivated(this, &SteamServerClientWrapper::OnGameOverlayActivated)
	{
		//Stuff.
	}

	STEAM_CALLBACK(SteamServerClientWrapper, OnP2PSessionConnectFail, P2PSessionConnectFail_t, m_CallbackP2PSessionConnectFail);

	STEAM_CALLBACK(SteamServerClientWrapper, OnLobbyGameCreated, LobbyGameCreated_t, m_LobbyGameCreated);

	STEAM_CALLBACK(SteamServerClientWrapper, OnIPCFailure, IPCFailure_t, m_IPCFailureCallback);

	STEAM_CALLBACK(SteamServerClientWrapper, OnSteamShutdown, SteamShutdown_t, m_SteamShutdownCallback);

	STEAM_CALLBACK(SteamServerClientWrapper, OnSteamServersConnected, SteamServersConnected_t, m_SteamServersConnected);

	STEAM_CALLBACK(SteamServerClientWrapper, OnSteamServersDisconnected, SteamServersDisconnected_t, m_SteamServersDisconnected);

	STEAM_CALLBACK(SteamServerClientWrapper, OnSteamServerConnectFailure, SteamServerConnectFailure_t, m_SteamServerConnectFailure);

	STEAM_CALLBACK(SteamServerClientWrapper, OnGameJoinRequested, GameRichPresenceJoinRequested_t, m_GameJoinRequested);

	STEAM_CALLBACK(SteamServerClientWrapper, OnGameOverlayActivated, GameOverlayActivated_t, m_CallbackGameOverlayActivated);
} *steam_server_client_wrapper;

void SteamServerClientWrapper::OnP2PSessionConnectFail(P2PSessionConnectFail_t *pCallback)
{
	if (c_SteamServerClientWrapper_OnP2PSessionConnectFail)
		(*c_SteamServerClientWrapper_OnP2PSessionConnectFail)(pCallback);
}

void SteamServerClientWrapper::OnLobbyGameCreated(LobbyGameCreated_t *pCallback)
{
	if (c_SteamServerClientWrapper_OnLobbyGameCreated)
		(*c_SteamServerClientWrapper_OnLobbyGameCreated)(pCallback);
}

void SteamServerClientWrapper::OnIPCFailure(IPCFailure_t *failure)
{
	if (c_SteamServerClientWrapper_OnIPCFailure)
		(*c_SteamServerClientWrapper_OnIPCFailure)(failure);
}

void SteamServerClientWrapper::OnSteamShutdown(SteamShutdown_t *callback)
{
	if (c_SteamServerClientWrapper_OnSteamShutdown)
		(*c_SteamServerClientWrapper_OnSteamShutdown)(callback);
}

void SteamServerClientWrapper::OnSteamServersConnected(SteamServersConnected_t *callback)
{
	if (c_SteamServerClientWrapper_OnSteamServersConnected)
		(*c_SteamServerClientWrapper_OnSteamServersConnected)(callback);
}

void SteamServerClientWrapper::OnSteamServersDisconnected(SteamServersDisconnected_t *callback)
{
	if (c_SteamServerClientWrapper_OnSteamServersDisconnected)
		(*c_SteamServerClientWrapper_OnSteamServersDisconnected)(callback);
}

void SteamServerClientWrapper::OnSteamServerConnectFailure(SteamServerConnectFailure_t *callback)
{
	if (c_SteamServerClientWrapper_OnSteamServerConnectFailure)
		(*c_SteamServerClientWrapper_OnSteamServerConnectFailure)(callback);
}

void SteamServerClientWrapper::OnGameJoinRequested(GameRichPresenceJoinRequested_t *pCallback)
{
	if (c_SteamServerClientWrapper_OnGameJoinRequested)
		(*c_SteamServerClientWrapper_OnGameJoinRequested)(pCallback);
}

void SteamServerClientWrapper::OnGameOverlayActivated(GameOverlayActivated_t *callback)
{
	if (c_SteamServerClientWrapper_OnGameOverlayActivated)
		(*c_SteamServerClientWrapper_OnGameOverlayActivated)(callback);
}

extern "C" void c_SteamServerClientWrapper_Instantiate()
{
	steam_server_client_wrapper = new SteamServerClientWrapper();
}

extern "C" void c_SteamServerClientWrapper_Destroy()
{
	delete steam_server_client_wrapper;
	steam_server_client_wrapper = nullptr;
}

extern "C" uint64_t c_LobbyGameCreated_t_m_ulSteamIDGameServer(void *LobbyGameCreated_t_instance)
{
	return static_cast<LobbyGameCreated_t*>(LobbyGameCreated_t_instance)->m_ulSteamIDGameServer;
}

extern "C" char* c_GameRichPresenceJoinRequested_t_m_rgchConnect(void *GameRichPresenceJoinRequested_t_instance)
{
	char* result = (char*)malloc(c_k_cchMaxRichPresenceValueLength * sizeof(char));
	memcpy(result, static_cast<GameRichPresenceJoinRequested_t*>(GameRichPresenceJoinRequested_t_instance)->m_rgchConnect, c_k_cchMaxRichPresenceValueLength);
	return result;
}

extern "C" void c_SteamFriends_ActivateGameOverlayInviteDialog(void *steamIDLobby)
{
	SteamFriends()->ActivateGameOverlayInviteDialog(*static_cast<CSteamID*>(steamIDLobby));
}