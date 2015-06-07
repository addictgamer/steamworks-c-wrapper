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

enum EServerMode
{
	eServerModeInvalid = 0,
	eServerModeNoAuthentication = 1,
	eServerModeAuthentication = 2,
	eServerModeAuthenticationAndSecure = 3,
};

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

void SteamGameServerNetworking_AcceptP2PSessionWithUser(void* steamIDRemote);


#endif