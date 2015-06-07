/*
 * Copyright (c) 2015 CIPRIAN ILIES
 * See LICENSE for details.
 */

#ifndef STEAM_WRAPPER_H
#define STEAM_WRAPPER_H

#include <stdint.h>

//Stuff.
bool SteamAPI_Init();

void SteamAPI_Shutdown();

bool SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID);

//What is this? Where is it defined? How do I wrap it? AAAAAAAAAAAAH.
//bool Steamworks_InitCEGLibrary();

bool SteamUser_BLoggedOn();

typedef enum EServerMode_t
{
	eServerModeInvalid = 0,
	eServerModeNoAuthentication = 1,
	eServerModeAuthentication = 2,
	eServerModeAuthenticationAndSecure = 3,
} EServerMode;

bool SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, EServerMode eServerMode, const char* pchVersionString);

void SteamGameServer_Shutdown();

/*
 * Note: The Steam API prototype looks like this: S_API ISteamGameServer* SteamGameServer().
 * This returns a void pointer to the return value of that function.
 * At this point in time, there isn't really much value in the return data except to check if it's NULL or something else,
 * seeing as the data being pointed to is a class.
 * What the intended purpose of the return data is, I don't know.
 */
void* SteamGameServer();

/*
 * Would it be better to create a struct with function pointers to all of these functions?
 */
void SteamGameServer_SetModDir(const char *pszModDir);

void SteamGameServer_SetProduct(const char *pszProduct);

void SteamGameServer_SetGameDescription(const char *pszGameDescription);

void SteamGameServer_LogOnAnonymous();

void SteamGameServer_EnableHeartbeats(bool bActive);

void SteamGameServer_LogOff();

/*
 * Note that the original function takes a CSteamID.
 * steamIDRemote should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 * I sure hope this void pointer is sufficient for dealing with CSteamID.
 */
void SteamGameServerNetworking_AcceptP2PSessionWithUser(void* steamIDRemote);

typedef enum EP2PSend_t
{
	k_EP2PSendUnreliable = 0,
	k_EP2PSendUnreliableNoDelay = 1,
	k_EP2PSendReliable = 2,
	k_EP2PSendReliableWithBuffering = 3,
} EP2PSend;

/*
 * NOTE: nChannel defaults to zero in the steam API. That does not happen here.
 * Because, you know, C.
 * NOTE 2: steamIDRemote should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
bool SteamGameServerNetworking_SendP2PPacket(void* steamIDRemote, const void *pubData, uint32_t cubData, EP2PSend eP2PSendType, int nChannel);

typedef enum EBeginAuthSessionResult_t
{
	k_EBeginAuthSessionResultOK = 0,
	k_EBeginAuthSessionResultInvalidTicket = 1,
	k_EBeginAuthSessionResultDuplicateRequest = 2,
	k_EBeginAuthSessionResultInvalidVersion = 3,
	k_EBeginAuthSessionResultGameMismatch = 4,
	k_EBeginAuthSessionResultExpiredTicket = 5,
} EBeginAuthSessionResult;

/*
 * NOTE: steamID should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
EBeginAuthSessionResult SteamGameServer_BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, void* steamID);

/*
 * NOTE: steamID should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
void SteamGameServer_EndAuthSession(void* steamID);

/*
 * NOTE: nChannel defaults to zero in the steam API. That is not so here because, you know, C.
 */
bool SteamGameServerNetworking_IsP2PPacketAvailable(uint32_t *pcubMsgSize, int nChannel);

/*
 * NOTE: psteamIDRemote should be a CSteamID pointer. It gets converted back to a CSteamID pointer in this function.
 * NOTE 2: nChannel defaults to zero in the steam API. That is not so here because, you know, C.
 */
bool SteamGameServerNetworking_ReadP2PPacket(void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize, void* psteamIDRemote, int nChannel);

uint64_t SteamGameServer_GetSteamID_ConvertToUInt64();

bool SteamGameServer_BSecure();

/*
 * NOTE: steamIDUser should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
void SteamGameServer_SendUserDisconnect(void* steamIDUser);

void SteamGameServer_RunCallbacks();

void SteamGameServer_SetMaxPlayerCount(int cPlayersMax);

void SteamGameServer_SetPasswordProtected(bool bPasswordProtected);

void SteamGameServer_SetServerName(const char *pszServerName);

void SteamGameServer_SetBotPlayerCount(int cBotplayers);

void SteamGameServer_SetMapName(const char *pszMapName);

bool SteamGameServer_BUpdateUserData(void* steamIDUser, const char *pchPlayerName, uint32_t uScore);

#endif