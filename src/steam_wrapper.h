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
 * Note that this function calls new to hold the data SteamMatchmaking()->GetLobbyOwner() returns.
 * TODO: Does that data need to be explicitly deleted? I'd assume so. Need to write a wrapper to do that?
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

bool c_SteamUtils_IsAPICallCompleted(ulong hSteamAPICall, bool *pbFailed);

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

#endif