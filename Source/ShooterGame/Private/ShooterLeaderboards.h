// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "ShooterTypes.h"
#include "Interfaces/OnlineLeaderboardInterface.h"

// these are normally exported from platform-specific tools
#define LEADERBOARD_STAT_SCORE			"ShooterAllTimeMatchResultsScore"
#define LEADERBOARD_STAT_KILLS			"ShooterAllTimeMatchResultsFrags"
#define LEADERBOARD_STAT_DEATHS			"ShooterAllTimeMatchResultsDeaths"
#define LEADERBOARD_STAT_MATCHESPLAYED	"ShooterAllTimeMatchResultsMatchesPlayed"

/**
 *	'AllTime' leaderboard read object
 */
class FShooterAllTimeMatchResultsRead : public FOnlineLeaderboardRead
{
public:

	FShooterAllTimeMatchResultsRead()
	{
		// Default properties
		LeaderboardName = TEXT("ShooterAllTimeMatchResults");  // Remove FName()
		SortedColumn = LEADERBOARD_STAT_SCORE;

		// Define default columns
		ColumnMetadata.Add(FColumnMetaData(LEADERBOARD_STAT_SCORE, EOnlineKeyValuePairDataType::Int32));
	}
};

/**
 *	'AllTime' leaderboard write object
 */
class FShooterAllTimeMatchResultsWrite : public FOnlineLeaderboardWrite
{
public:

	FShooterAllTimeMatchResultsWrite()
	{
		// Default properties
		LeaderboardNames.Add(TEXT("ShooterAllTimeMatchResults"));
		RatedStat = LEADERBOARD_STAT_SCORE;
		DisplayFormat = ELeaderboardFormat::Number;
		SortMethod = ELeaderboardSort::Descending;
		UpdateMethod = ELeaderboardUpdateMethod::KeepBest;
	}
};

