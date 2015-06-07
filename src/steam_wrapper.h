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

#endif