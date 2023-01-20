#ifndef COMMANDS
#define COMMANDS
#include "Joystick.h"

static const command_set Sync_Controller = {
	false, // Repeat
	{
		{ NOTHING,  250 },
		{ TRIGGERS,   5 },
		{ NOTHING,  150 },
		{ TRIGGERS,   5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  250 }
	}
};

static const command_set Spam_A = {
	true, //Repeat
	{
		{ NOTHING,  150 },
		{ A,          5 }
	}
};

#define RELEASE_POKEMON_MACRO // Select Pokemon\
		{ NOTHING,  150 },\
		{ A,          5 },\
		// Select 'Release'\
		{ NOTHING,  150 },\
		{ UP,         5 },\
		{ NOTHING,  150 },\
		{ UP,         5 },\
		{ NOTHING,  150 },\
		{ A,          5 },\
		// Are we sure?\
		{ NOTHING,  150 },\
		{ UP,         5 },\
		{ NOTHING,  150 },\
		{ A,          5 }
static const command_set Release_Entire_Box = {
	false, //Repeat
	{
		RELEASE_POKEMON_MACRO,
		{ NOTHING,  150 },
		{ RIGHT,      5 }
	}
}

#endif