/*
 * Copyright (c) 2015 CIPRIAN ILIES
 * See LICENSE for details.
 */

#ifndef STEAM_WRAPPER_H
#define STEAM_WRAPPER_H

#include <stdint.h>

bool c_SteamAPI_Init();

void c_SteamAPI_Shutdown();

bool c_SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID);

bool c_SteamUser_BLoggedOn();

void c_SteamAPI_RunCallbacks();

typedef enum c_EServerMode_t
{
	c_eServerModeInvalid = 0,
	c_eServerModeNoAuthentication = 1,
	c_eServerModeAuthentication = 2,
	c_eServerModeAuthenticationAndSecure = 3,
} c_EServerMode;

bool c_SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, c_EServerMode eServerMode, const char* pchVersionString);

void c_SteamGameServer_Shutdown();

/*
 * Note: The Steam API prototype looks like this: S_API ISteamGameServer* SteamGameServer().
 * This returns a void pointer to the return value of that function.
 * At this point in time, there isn't really much value in the return data except to check if it's NULL or something else,
 * seeing as the data being pointed to is a class.
 * What the intended purpose of the return data is, I don't know.
 */
void* c_SteamGameServer();

/*
 * Would it be better to create a struct with function pointers to all of these functions?
 */
void c_SteamGameServer_SetModDir(const char *pszModDir);

void c_SteamGameServer_SetProduct(const char *pszProduct);

void c_SteamGameServer_SetGameDescription(const char *pszGameDescription);

void c_SteamGameServer_LogOnAnonymous();

void c_SteamGameServer_EnableHeartbeats(bool bActive);

void c_SteamGameServer_LogOff();

/*
 * Note that the original function takes a CSteamID.
 * steamIDRemote should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 * I sure hope this void pointer is sufficient for dealing with CSteamID.
 */
void c_SteamGameServerNetworking_AcceptP2PSessionWithUser(void* steamIDRemote);

typedef enum c_EP2PSend_t
{
	c_k_EP2PSendUnreliable = 0,
	c_k_EP2PSendUnreliableNoDelay = 1,
	c_k_EP2PSendReliable = 2,
	c_k_EP2PSendReliableWithBuffering = 3,
} c_EP2PSend;

/*
 * NOTE: nChannel defaults to zero in the steam API. That does not happen here.
 * Because, you know, C.
 * NOTE 2: steamIDRemote should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
bool c_SteamGameServerNetworking_SendP2PPacket(void* steamIDRemote, const void *pubData, uint32_t cubData, c_EP2PSend eP2PSendType, int nChannel);

typedef enum c_EBeginAuthSessionResult_t
{
	c_k_EBeginAuthSessionResultOK = 0,
	c_k_EBeginAuthSessionResultInvalidTicket = 1,
	c_k_EBeginAuthSessionResultDuplicateRequest = 2,
	c_k_EBeginAuthSessionResultInvalidVersion = 3,
	c_k_EBeginAuthSessionResultGameMismatch = 4,
	c_k_EBeginAuthSessionResultExpiredTicket = 5,
} c_EBeginAuthSessionResult;

/*
 * NOTE: steamID should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
c_EBeginAuthSessionResult c_SteamGameServer_BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, void* steamID);

/*
 * NOTE: steamID should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
void c_SteamGameServer_EndAuthSession(void* steamID);

/*
 * NOTE: nChannel defaults to zero in the steam API. That is not so here because, you know, C.
 */
bool c_SteamGameServerNetworking_IsP2PPacketAvailable(uint32_t *pcubMsgSize, int nChannel);

/*
 * NOTE: psteamIDRemote should be a CSteamID pointer. It gets converted back to a CSteamID pointer in this function.
 * NOTE 2: nChannel defaults to zero in the steam API. That is not so here because, you know, C.
 */
bool c_SteamGameServerNetworking_ReadP2PPacket(void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize, void* psteamIDRemote, int nChannel);

uint64_t c_SteamGameServer_GetSteamID_ConvertToUInt64();

bool c_SteamGameServer_BSecure();

/*
 * NOTE: steamIDUser should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
void c_SteamGameServer_SendUserDisconnect(void* steamIDUser);

void c_SteamGameServer_RunCallbacks();

void c_SteamGameServer_SetMaxPlayerCount(int cPlayersMax);

void c_SteamGameServer_SetPasswordProtected(bool bPasswordProtected);

void c_SteamGameServer_SetServerName(const char *pszServerName);

void c_SteamGameServer_SetBotPlayerCount(int cBotplayers);

void c_SteamGameServer_SetMapName(const char *pszMapName);

bool c_SteamGameServer_BUpdateUserData(void* steamIDUser, const char *pchPlayerName, uint32_t uScore);

//Will this work? I foresee this being a possible source of problems.
#ifndef STEAM_CALLBACK
#define STEAM_CALLBACK(thisclass, func, param, var) CCallback< thisclass, param, false > var; void func(param *pParam)
#endif

int64_t c_SteamUtils_GetAppID();

/*
 * NOTE: The steam api returns a pointer to ISteamUser. Since C can't see classes, this function returns false if SteamUser() returns NULL, true otherwise (useful for checking if steam was initialized, for example).
 */
bool c_SteamUser();

/*
 * Note that this function calls new to hold the data SteamUser()->GetSteamID() returns.
 * NOTE: This function allocates data. Call c_Free_CSteamID() on the pointer returned by this function when you're done using it to free the memory.
 */
void* c_SteamUser_GetSteamID();

void c_Free_CSteamID(void *steamID);

/*
 * NOTE: This function allocates data. Call c_Free_CSteamID() on the pointer returned by this function when you're done using it to free the memory.
 */
void* c_AllocateNew_CSteamID();

/*
 * NOTE: The steam api returns a pointer to ISteamUserStats. Since C can't see classes, this function returns false if SteamUserStats() returns NULL, true otherwise (useful for checking if steam was initialized, for example).
 */
bool c_SteamUserStats();

bool c_SteamUserStats_RequestCurrentStats();

bool c_SteamUserStats_SetAchievement(const char *pchName);

int c_SteamUserStats_GetAchievementIcon(const char *pchName);

bool c_SteamUserStats_SetStat(const char *pchName, int32_t nData);

bool c_SteamUserStats_UpdateAvgRateStat(const char *pchName, float flCountThisSession, double dSessionLength);

/*
 * NOTE: This is an overloaded function, which is not possible in C, so it must be worked around with trickery.
 * Such as renaming the function.
 */
bool c_SteamUserStats_GetStat_Int(const char *pchName, int32_t *pData);
bool c_SteamUserStats_GetStat_Float(const char *pchName, float *pData);

bool c_SteamUserStats_StoreStats();

const char* c_SteamUserStats_GetAchievementDisplayAttribute(const char *pchName, const char *pchKey);

/*
 * NOTE: In C++, this would be used like so:
 CSteamID steamIDLobby;
 ...
 steamIDLobby.IsValid();
 * This is C, so pass a void pointer to the CSteamID you want to check.
 */
bool c_CSteamID_IsValid(void *CSteamID_instance);

/*
 * NOTE: In C++, this would be used like so:
 CSteamID steamIDLobby;
 ...
 SteamMatchmaking()->GetNumLobbyMembers(steamIDLobby);
 * This is C, so pass a void pointer to the CSteamID you want to use.
 */
int c_SteamMatchmaking_GetNumLobbyMembers(void *steamIDLobby);

/*
 * NOTE: Returns a void pointer to a CSteamID.
 * In C++, this would be used like so:
 CSteamID steamIDLobby;
 ...
 CSteamID steamIDLobbyMember = SteamMatchmaking()->GetLobbyMemberByIndex(steamIDLobby, index);
 * This is C, so pass a void pointer to the CSteamID you want to use.
 * Note that this function calls new to hold the data SteamMatchmaking()->GetLobbyMemberByIndex() returns.
 * NOTE: This function allocates data. Call c_Free_CSteamID() on the pointer returned by this function when you're done using it to free the memory.
 */
void* c_SteamMatchmaking_GetLobbyMemberByIndex(void *steamIDLobby, int iMember);

/*
 * NOTE: In C++, this would be used like so:
 CSteamID steamIDLobbyMember;
 ...
 const char *name = SteamFriends()->GetFriendPersonaName(steamIDLobbyMember);
 * This is C, so pass a void pointer to the CSteamID you want to use.
 */
const char* c_SteamFriends_GetFriendPersonaName(void *steamIDLobbyMember);

const char* c_SteamFriends_GetPersonaName();

/*
 * NOTE: In C++, this would be used like so:
 CSteamID steamIDLobby;
 CSteamID steamIDUser;
 ...
 const char *data = SteamMatchmaking()->GetLobbyMemberData(steamIDLobby, steamIDLobbyMember, "whatever");
 * This is C, so pass void pointers of the CSteamIDs you want to use to steamIDLobby and steamIDUser.
 */
const char* c_SteamMatchmaking_GetLobbyMemberData(void *steamIDLobby, void *steamIDUser, const char *pchKey);

/*
 * NOTE: In C++, this would be used like so:
 CSteamID steamIDLobby;
 ...
 CSteamID id = SteamMatchmaking()->GetLobbyOwner(steamIDLobby);
 * This is C, so pass a void pointer of the CSteamID you want to use to steamIDLobby.
 * NOTE: Call c_Free_CSteamID() on the void pointer returned by this when done with it.
 */
void* c_SteamMatchmaking_GetLobbyOwner(void *steamIDLobby);

/*
 * NOTE: In C++, this would be used like so:
 CSteamID steamIDUser;
 CSteamID steamIDLobby;
 ...
 SteamFriends()->IsUserInSource(steamIDUser, steamIDLobby);
 * This is C, so pass void pointers of the CSteamIDs you want to use to steamIDUser and steamIDSource.
 */
bool c_SteamFriends_IsUserInSource(void *steamIDUser, void *steamIDSource);

typedef uint64_t c_SteamAPICall_t;

c_SteamAPICall_t c_SteamMatchmaking_RequestLobbyList();

/*
 * NOTE: This function calls new to hold the data SteamMatchmaking()->GetLobbyByIndex() returns.
 * NOTE: This function allocates data. Call c_Free_CSteamID() on the pointer returned by this function when you're done using it to free the memory.
 */
void* c_SteamMatchmaking_GetLobbyByIndex(int iLobby);

/*
 * NOTE: In C++, this would be used like so:
 CSteamID steamIDLobby;
 ...
 SteamMatchmaking()->RequestLobbyData(steamIDLobby);
 * This is C, so pass a void pointer of the CSteamID you want to use to steamIDLobby.
 */
bool c_SteamMatchmaking_RequestLobbyData(void *steamIDLobby);

typedef uint32_t c_AccountID_t;

/*
 * NOTE: In C++, this would be used like so:
 CSteamID id;
 ...
 AccountID_t account_id = id.GetAccountID();
 * This is C, so pass a void pointer to the CSteamID you want to call GetAccountID() from.
 */
//steamIDLobby.GetAccountID()
c_AccountID_t c_CSteamID_GetAccountID(void *CSteamID_instance);

bool c_SteamUtils_IsAPICallCompleted(unsigned long hSteamAPICall, bool *pbFailed);

bool c_SteamUtils_GetAPICallResult(c_SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed);

/*
 * NOTE: This is C, so pass a void pointer to the LobbyMatchList_t you want to grab the m_nLobbiesMatching variable from.
 */
uint32_t c_LobbyMatchList_t_m_nLobbiesMatching(void *LobbyMatchList_t_instance);

typedef enum c_ELobbyComparison_t
{
	c_k_ELobbyComparisonEqualToOrLessThan = -2,
	c_k_ELobbyComparisonLessThan = -1,
	c_k_ELobbyComparisonEqual = 0,
	c_k_ELobbyComparisonGreaterThan = 1,
	c_k_ELobbyComparisonEqualToOrGreaterThan = 2,
	c_k_ELobbyComparisonNotEqual = 3,
} c_ELobbyComparison;

void c_SteamMatchmaking_AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, c_ELobbyComparison eComparisonType);

void c_SteamMatchmaking_AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, c_ELobbyComparison eComparisonType);

void c_SteamMatchmaking_AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo);

void c_SteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable);

typedef enum c_ELobbyType_t
{
	c_k_ELobbyTypePrivate = 0,
	c_k_ELobbyTypeFriendsOnly = 1,
	c_k_ELobbyTypePublic = 2,
	c_k_ELobbyTypeInvisible = 3,
} c_ELobbyType;

c_SteamAPICall_t c_SteamMatchmaking_CreateLobby(c_ELobbyType eLobbyType, int cMaxMembers);

/*
 * NOTE: This is C, so pass a void pointer to the CSteamID you want to use for steamIDLobby.
 */
c_SteamAPICall_t c_SteamMatchmaking_JoinLobby(void *steamIDLobby);

/*
 * NOTE: This is C, so pass a void pointer to the CSteamID you want to use for steamIDLobby.
 */
bool c_SteamMatchmaking_SetLobbyData(void *steamIDLobby, const char *pchKey, const char *pchValue);

/*
 * NOTE: This is C, so pass a void pointer to the CSteamID you want to use for steamIDLobby.
 */
bool c_SteamMatchmaking_DeleteLobbyData(void *steamIDLobby, const char *pchKey);

/*
 * NOTE: This is C, so pass a void pointer to the CSteamID you want to use for steamIDLobby.
 */
int c_SteamMatchmaking_GetLobbyDataCount(void *steamIDLobby);

/*
 * NOTE: This is C, so pass a void pointer to the CSteamID you want to use for steamIDLobby.
 */
bool c_SteamMatchmaking_GetLobbyDataByIndex(void *steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize);

/*
 * NOTE: This is C, so pass a void pointer to the CSteamID you want to use for steamIDLobby.
 */
bool c_SteamMatchmaking_SendLobbyChatMsg(void *steamIDLobby, const void *pvMsgBody, int cubMsgBody);

typedef enum c_EChatEntryType_t
{
	c_k_EChatEntryTypeInvalid = 0,
	c_k_EChatEntryTypeChatMsg = 1,
	c_k_EChatEntryTypeTyping = 2,
	c_k_EChatEntryTypeInviteGame = 3,
	c_k_EChatEntryTypeEmote = 4,
	c_k_EChatEntryTypeLeftConversation = 6,
	c_k_EChatEntryTypeEntered = 7,
	c_k_EChatEntryTypeWasKicked = 8,
	c_k_EChatEntryTypeWasBanned = 9,
	c_k_EChatEntryTypeDisconnected = 10,
	c_k_EChatEntryTypeHistoricalChat = 11,
	c_k_EChatEntryTypeReserved1 = 12,
	c_k_EChatEntryTypeReserved2 = 13,
	c_k_EChatEntryTypeLinkBlocked = 14,
} c_EChatEntryType;

/*
 * NOTE: This is C, so pass void pointers to the CSteamIDs you want to use for steamIDLobby and pSteamIDUser.
 */
int c_SteamMatchmaking_GetLobbyChatEntry(void *steamIDLobby, int iChatID, void *pSteamIDUser, void *pvData, int cubData, c_EChatEntryType *peChatEntryType);

bool c_SteamFriends_SetRichPresence(const char *pchKey, const char *pchValue);

int c_SteamFriends_GetFriendCount(int iFriendFlags);

/*
 * NOTE: This is C, so pass void pointers to the CSteamIDs you want to use for steamIDLobby and steamIDInvitee.
 */
bool c_SteamMatchmaking_InviteUserToLobby(void *steamIDLobby, void *steamIDInvitee);

void c_SteamFriends_ActivateGameOverlay(const char *pchDialog);

/*
 * NOTE: This is C, so pass a void pointer to the CSteamID you want to use for steamIDLobby.
 */
void c_SteamMatchmaking_LeaveLobby(void *steamIDLobby);

typedef enum c_EFriendFlags_t
{
	c_k_EFriendFlagNone = 0x00,
	c_k_EFriendFlagBlocked = 0x01,
	c_k_EFriendFlagFriendshipRequested = 0x02,
	c_k_EFriendFlagImmediate = 0x04,
	c_k_EFriendFlagClanMember = 0x08,
	c_k_EFriendFlagOnGameServer = 0x10,
	c_k_EFriendFlagRequestingFriendship = 0x80,
	c_k_EFriendFlagRequestingInfo = 0x100,
	c_k_EFriendFlagIgnored = 0x200,
	c_k_EFriendFlagIgnoredFriend = 0x400,
	c_k_EFriendFlagSuggested = 0x800,
	c_k_EFriendFlagAll = 0xFFFF,
} c_EFriendFlags;

/*
 * NOTE: This is C, so pass a void pointer to the CSteamID you want to use for steamIDFriend and a void pointer to the FriendGameInfo_t you want to use for pFriendGameInfo.
 */
bool c_SteamFriends_GetFriendGamePlayed(void *steamIDFriend, void *pFriendGameInfo);

/*
 * Returns the CSteamID data member m_steamIDLobby of FriendGameInfo_t.
 * NOTE: This is C, so pass a void pointer to the FriendGameInfo_t you want to use for FriendGameInfo_t_instance.
 * NOTE: This function allocates data. Call c_Free_CSteamID() on the pointer returned by this function when you're done using it to free the memory.
 */
void* c_FriendGameInfo_t_m_steamIDLobby(void *FriendGameInfo_t_instance);

/*
 * Takes a void pointer to the P2PSessionRequest_t you want to extract m_steamIDRemote from and returns a void pointer to m_steamIDRemote.
 * NOTE: This is C, so pass a void pointer to the P2PSessionRequest_t you want to use for P2PSessionRequest_t_instance.
 * NOTE: This function allocates data. Call c_Free_CSteamID() on the pointer returned by this function when you're done using it to free the memory.
 */
void* c_P2PSessionRequest_t_m_steamIDRemote(void *P2PSessionRequest_t_instance);

/*
 * Function pointers to handle steam callbacks.
 * NOTE: You'll have to implement these yourself. But first, call c_SteamServerWrapper_Instantiate().
 */
void (*c_SteamServerWrapper_OnSteamServersConnected)(void *pLogonSuccess);
void (*c_SteamServerWrapper_OnSteamServersConnectFailure)(void *pConnectFailure);
void (*c_SteamServerWrapper_OnSteamServersDisconnected)(void *pLoggedOff);
void (*c_SteamServerWrapper_OnPolicyResponse)(void *pPolicyResponse);
void (*c_SteamServerWrapper_OnValidateAuthTicketResponse)(void *pResponse);
void (*c_SteamServerWrapper_OnP2PSessionRequest)(void *p_Callback);
void (*c_SteamServerWrapper_OnP2PSessionConnectFail)(void *pCallback);

/*
 * NOTE: Call c_SteamServerWrapper_Destroy() when you're done using this to free the memory.
 */
void c_SteamServerWrapper_Instantiate();

void c_SteamServerWrapper_Destroy();

/*
 * Takes a void pointer to the P2PSessionConnectFail_t you want to extract m_steamIDRemote from and returns a void pointer to m_steamIDRemote.
 * NOTE: This is C, so pass a void pointer to the P2PSessionConnectFail_t you want to use for P2PSessionConnectFail_t_instance.
 * NOTE: This function allocates data. Call c_Free_CSteamID() on the pointer returned by this function when you're done using it to free the memory.
 */
void* c_P2PSessionConnectFail_t_m_steamIDRemote(void *P2PSessionConnectFail_t_instance);

typedef enum c_EAuthSessionResponse_t
{
	c_k_EAuthSessionResponseOK = 0,
	c_k_EAuthSessionResponseUserNotConnectedToSteam = 1,
	c_k_EAuthSessionResponseNoLicenseOrExpired = 2,
	c_k_EAuthSessionResponseVACBanned = 3,
	c_k_EAuthSessionResponseLoggedInElseWhere = 4,
	c_k_EAuthSessionResponseVACCheckTimedOut = 5,
	c_k_EAuthSessionResponseAuthTicketCanceled = 6,
	c_k_EAuthSessionResponseAuthTicketInvalidAlreadyUsed = 7,
	c_k_EAuthSessionResponseAuthTicketInvalid = 8,
	c_k_EAuthSessionResponsePublisherIssuedBan = 9,
} c_EAuthSessionResponse;

/*
 * Takes a void pointer to the ValidateAuthTicketResponse_t you want to extract EAuthSessionResponse from.
 * NOTE: This is C, so pass a void pointer to the ValidateAuthTicketResponse_t you want to use for ValidateAuthTicketResponse_t_instance.
 */
c_EAuthSessionResponse c_ValidateAuthTicketResponse_t_EAuthSessionResponse(void *ValidateAuthTicketResponse_t_instance);

/*
 * Takes a void pointer to the ValidateAuthTicketResponse_t you want to extract m_SteamID from and returns a void pointer to m_SteamID.
 * NOTE: This is C, so pass a void pointer to the ValidateAuthTicketResponse_t you want to use for ValidateAuthTicketResponse_t_instance.
 * NOTE: This function allocates data. Call c_Free_CSteamID() on the pointer returned by this function when you're done using it to free the memory.
 */
void* c_ValidateAuthTicketResponse_t_m_SteamID(void *ValidateAuthTicketResponse_t_instance);

/*
 * Function Pointers to handle steam callbacks.
 * NOTE: You'll have to implement these yourself. But first, call c_SteamServerClientWrapper_Instantiate().
 */
void (*c_SteamServerClientWrapper_OnLobbyGameCreated)(void *pCallback);
void (*c_SteamServerClientWrapper_OnGameJoinRequested)(void *pCallback);
void (*c_SteamServerClientWrapper_OnAvatarImageLoaded)(void *pCallback);
void (*c_SteamServerClientWrapper_OnSteamServersConnected)(void *callback);
void (*c_SteamServerClientWrapper_OnSteamServersDisconnected)(void *callback);
void (*c_SteamServerClientWrapper_OnSteamServerConnectFailure)(void *callback);
void (*c_SteamServerClientWrapper_OnGameOverlayActivated)(void *callback);
void (*c_SteamServerClientWrapper_OnGameWebCallback)(void *callback);
void (*c_SteamServerClientWrapper_OnWorkshopItemInstalled)(void *pParam);
void (*c_SteamServerClientWrapper_OnP2PSessionConnectFail)(void *pCallback);
void (*c_SteamServerClientWrapper_OnIPCFailure)(void *failure);
void (*c_SteamServerClientWrapper_OnSteamShutdown)(void *callback);
void (*c_SteamServerClientWrapper_OnLobbyCreated)(void *pCallback, bool bIOFailure); //Where pCallback is a pointer to type LobbyCreated_t.
void (*c_SteamServerClientWrapper_OnLobbyEntered)(void *pCallback, bool bIOFailure); //Where pCallback is a pointer to type LobbyEnter_t.
void (*c_SteamServerClientWrapper_OnRequestEncryptedAppTicket)(void *pEncryptedAppTicketResponse, bool bIOFailure); //Where pEncryptedAppTicketResponse is of type EncryptedAppTicketResponse_t.

/*
 * NOTE: Call c_SteamServerClientWrapper_Destroy() when you're done using this to free to memory.
 */
void c_SteamServerClientWrapper_Instantiate();

void c_SteamServerClientWrapper_Destroy();

/*
 * Takes a void pointer to the LobbyGameCreated_t you want to extract m_ulSteamIDGameServer from.
 * NOTE: This is C, so pass a void pointer to the LobbyGameCreated_t you want to use for LobbyGameCreated_t_instance.
 */
uint64_t c_LobbyGameCreated_t_m_ulSteamIDGameServer(void *LobbyGameCreated_t_instance);

enum { c_k_cchMaxRichPresenceValueLength = 256 };

/*
 * Takes a void pointer to the GameRichPresenceJoinRequested_t you want to extract m_rgchConnect from.
 * The char array returned is of size c_k_cchMaxRichPresenceValueLength.
 * NOTE: You are responsible for freeing the char array returned by this function.
 */
char* c_GameRichPresenceJoinRequested_t_m_rgchConnect(void *GameRichPresenceJoinRequested_t_instance);

/*
 * steamIDLobby should be a CSteamID pointer.
 */
void c_SteamFriends_ActivateGameOverlayInviteDialog(void *steamIDLobby);

/*
 * GameOverlayActivated_t_instance is a pointer to a GameOverlayActivated_t
 */
uint8_t c_GameOverlayActivated_t_m_bActive(void *GameOverlayActivated_t_instance);

// General result codes
typedef enum c_EResult
{
	c_k_EResultOK	= 1,							// success
	c_k_EResultFail = 2,							// generic failure 
	c_k_EResultNoConnection = 3,					// no/failed network connection
//	c_k_EResultNoConnectionRetry = 4,				// OBSOLETE - removed
	c_k_EResultInvalidPassword = 5,				// password/ticket is invalid
	c_k_EResultLoggedInElsewhere = 6,				// same user logged in elsewhere
	c_k_EResultInvalidProtocolVer = 7,			// protocol version is incorrect
	c_k_EResultInvalidParam = 8,					// a parameter is incorrect
	c_k_EResultFileNotFound = 9,					// file was not found
	c_k_EResultBusy = 10,							// called method busy - action not taken
	c_k_EResultInvalidState = 11,					// called object was in an invalid state
	c_k_EResultInvalidName = 12,					// name is invalid
	c_k_EResultInvalidEmail = 13,					// email is invalid
	c_k_EResultDuplicateName = 14,				// name is not unique
	c_k_EResultAccessDenied = 15,					// access is denied
	c_k_EResultTimeout = 16,						// operation timed out
	c_k_EResultBanned = 17,						// VAC2 banned
	c_k_EResultAccountNotFound = 18,				// account not found
	c_k_EResultInvalidSteamID = 19,				// steamID is invalid
	c_k_EResultServiceUnavailable = 20,			// The requested service is currently unavailable
	c_k_EResultNotLoggedOn = 21,					// The user is not logged on
	c_k_EResultPending = 22,						// Request is pending (may be in process, or waiting on third party)
	c_k_EResultEncryptionFailure = 23,			// Encryption or Decryption failed
	c_k_EResultInsufficientPrivilege = 24,		// Insufficient privilege
	c_k_EResultLimitExceeded = 25,				// Too much of a good thing
	c_k_EResultRevoked = 26,						// Access has been revoked (used for revoked guest passes)
	c_k_EResultExpired = 27,						// License/Guest pass the user is trying to access is expired
	c_k_EResultAlreadyRedeemed = 28,				// Guest pass has already been redeemed by account, cannot be acked again
	c_k_EResultDuplicateRequest = 29,				// The request is a duplicate and the action has already occurred in the past, ignored this time
	c_k_EResultAlreadyOwned = 30,					// All the games in this guest pass redemption request are already owned by the user
	c_k_EResultIPNotFound = 31,					// IP address not found
	c_k_EResultPersistFailed = 32,				// failed to write change to the data store
	c_k_EResultLockingFailed = 33,				// failed to acquire access lock for this operation
	c_k_EResultLogonSessionReplaced = 34,
	c_k_EResultConnectFailed = 35,
	c_k_EResultHandshakeFailed = 36,
	c_k_EResultIOFailure = 37,
	c_k_EResultRemoteDisconnect = 38,
	c_k_EResultShoppingCartNotFound = 39,			// failed to find the shopping cart requested
	c_k_EResultBlocked = 40,						// a user didn't allow it
	c_k_EResultIgnored = 41,						// target is ignoring sender
	c_k_EResultNoMatch = 42,						// nothing matching the request found
	c_k_EResultAccountDisabled = 43,
	c_k_EResultServiceReadOnly = 44,				// this service is not accepting content changes right now
	c_k_EResultAccountNotFeatured = 45,			// account doesn't have value, so this feature isn't available
	c_k_EResultAdministratorOK = 46,				// allowed to take this action, but only because requester is admin
	c_k_EResultContentVersion = 47,				// A Version mismatch in content transmitted within the Steam protocol.
	c_k_EResultTryAnotherCM = 48,					// The current CM can't service the user making a request, user should try another.
	c_k_EResultPasswordRequiredToKickSession = 49,// You are already logged in elsewhere, this cached credential login has failed.
	c_k_EResultAlreadyLoggedInElsewhere = 50,		// You are already logged in elsewhere, you must wait
	c_k_EResultSuspended = 51,					// Long running operation (content download) suspended/paused
	c_k_EResultCancelled = 52,					// Operation canceled (typically by user: content download)
	c_k_EResultDataCorruption = 53,				// Operation canceled because data is ill formed or unrecoverable
	c_k_EResultDiskFull = 54,						// Operation canceled - not enough disk space.
	c_k_EResultRemoteCallFailed = 55,				// an remote call or IPC call failed
	c_k_EResultPasswordUnset = 56,				// Password could not be verified as it's unset server side
	c_k_EResultExternalAccountUnlinked = 57,		// External account (PSN, Facebook...) is not linked to a Steam account
	c_k_EResultPSNTicketInvalid = 58,				// PSN ticket was invalid
	c_k_EResultExternalAccountAlreadyLinked = 59,	// External account (PSN, Facebook...) is already linked to some other account, must explicitly request to replace/delete the link first
	c_k_EResultRemoteFileConflict = 60,			// The sync cannot resume due to a conflict between the local and remote files
	c_k_EResultIllegalPassword = 61,				// The requested new password is not legal
	c_k_EResultSameAsPreviousValue = 62,			// new value is the same as the old one ( secret question and answer )
	c_k_EResultAccountLogonDenied = 63,			// account login denied due to 2nd factor authentication failure
	c_k_EResultCannotUseOldPassword = 64,			// The requested new password is not legal
	c_k_EResultInvalidLoginAuthCode = 65,			// account login denied due to auth code invalid
	c_k_EResultAccountLogonDeniedNoMail = 66,		// account login denied due to 2nd factor auth failure - and no mail has been sent
	c_k_EResultHardwareNotCapableOfIPT = 67,		// 
	c_k_EResultIPTInitError = 68,					// 
	c_k_EResultParentalControlRestricted = 69,	// operation failed due to parental control restrictions for current user
	c_k_EResultFacebookQueryError = 70,			// Facebook query returned an error
	c_k_EResultExpiredLoginAuthCode = 71,			// account login denied due to auth code expired
	c_k_EResultIPLoginRestrictionFailed = 72,
	c_k_EResultAccountLockedDown = 73,
	c_k_EResultAccountLogonDeniedVerifiedEmailRequired = 74,
	c_k_EResultNoMatchingURL = 75,
	c_k_EResultBadResponse = 76,					// parse failure, missing field, etc.
	c_k_EResultRequirePasswordReEntry = 77,		// The user cannot complete the action until they re-enter their password
	c_k_EResultValueOutOfRange = 78,				// the value entered is outside the acceptable range
	c_k_EResultUnexpectedError = 79,				// something happened that we didn't expect to ever happen
	c_k_EResultDisabled = 80,						// The requested service has been configured to be unavailable
	c_k_EResultInvalidCEGSubmission = 81,			// The set of files submitted to the CEG server are not valid !
	c_k_EResultRestrictedDevice = 82,				// The device being used is not allowed to perform this action
	c_k_EResultRegionLocked = 83,					// The action could not be complete because it is region restricted
	c_k_EResultRateLimitExceeded = 84,			// Temporary rate limit exceeded, try again later, different from c_k_EResultLimitExceeded which may be permanent
	c_k_EResultAccountLoginDeniedNeedTwoFactor = 85,	// Need two-factor code to login
	c_k_EResultItemDeleted = 86,					// The thing we're trying to access has been deleted
	c_k_EResultAccountLoginDeniedThrottle = 87,	// login attempt failed, try to throttle response to possible attacker
	c_k_EResultTwoFactorCodeMismatch = 88,		// two factor code mismatch
	c_k_EResultTwoFactorActivationCodeMismatch = 89,	// activation code for two-factor didn't match
	c_k_EResultAccountAssociatedToMultiplePartners = 90,	// account has been associated with multiple partners
	c_k_EResultNotModified = 91,					// data not modified
	c_k_EResultNoMobileDevice = 92,				// the account does not have a mobile device associated with it
	c_k_EResultTimeNotSynced = 93,				// the time presented is out of range or tolerance
	c_k_EResultSmsCodeFailed = 94,				// SMS code failure (no match, none pending, etc.)
	c_k_EResultAccountLimitExceeded = 95,			// Too many accounts access this resource
	c_k_EResultAccountActivityLimitExceeded = 96,	// Too many changes to this account
	c_k_EResultPhoneActivityLimitExceeded = 97,	// Too many changes to this phone
	c_k_EResultRefundToWallet = 98,				// Cannot refund to payment method, must use wallet
	c_k_EResultEmailSendFailure = 99,				// Cannot send an email
	c_k_EResultNotSettled = 100,					// Can't perform operation till payment has settled
} c_EResult;

c_EResult c_LobbyCreated_Result(void *pCallback);
void* c_LobbyCreated_Lobby(void *pCallback);

#endif