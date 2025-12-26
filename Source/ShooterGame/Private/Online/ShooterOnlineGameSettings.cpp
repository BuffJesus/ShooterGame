// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterOnlineGameSettings.h"
#include "ShooterGame.h"

// UE5: These search query constants were removed/moved in UE5 Online Subsystem
// Define them locally for backward compatibility
#ifndef SEARCH_PRESENCE
#define SEARCH_PRESENCE FName(TEXT("PRESENCESEARCH"))
#endif

#ifndef SEARCH_LOBBIES
#define SEARCH_LOBBIES FName(TEXT("LOBBYSEARCH"))
#endif

#ifndef SEARCH_DEDICATED_ONLY
#define SEARCH_DEDICATED_ONLY FName(TEXT("DEDICATEDONLY"))
#endif

#ifndef SEARCH_EMPTY_SERVERS_ONLY
#define SEARCH_EMPTY_SERVERS_ONLY FName(TEXT("EMPTYONLY"))
#endif


FShooterOnlineSessionSettings::FShooterOnlineSessionSettings(bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	NumPublicConnections = MaxNumPlayers;
	if (NumPublicConnections < 0)
	{
		NumPublicConnections = 0;
	}
	NumPrivateConnections = 0;
	bIsLANMatch = bIsLAN;
	bShouldAdvertise = true;
	bAllowJoinInProgress = true;
	bAllowInvites = true;
	bUsesPresence = bIsPresence;
	bAllowJoinViaPresence = true;
	bAllowJoinViaPresenceFriendsOnly = false;
}

FShooterOnlineSearchSettings::FShooterOnlineSearchSettings(bool bSearchingLAN, bool bSearchingPresence)
{
	bIsLanQuery = bSearchingLAN;
	MaxSearchResults = 10;
	PingBucketSize = 50;

	if (bSearchingPresence)
	{
		QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
	}
}

FShooterOnlineSearchSettingsEmptyDedicated::FShooterOnlineSearchSettingsEmptyDedicated(bool bSearchingLAN, bool bSearchingPresence) :
	FShooterOnlineSearchSettings(bSearchingLAN, bSearchingPresence)
{
	QuerySettings.Set(SEARCH_DEDICATED_ONLY, true, EOnlineComparisonOp::Equals);
	QuerySettings.Set(SEARCH_EMPTY_SERVERS_ONLY, true, EOnlineComparisonOp::Equals);
}