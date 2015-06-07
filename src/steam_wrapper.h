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

#endif