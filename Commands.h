#ifndef COMMANDS
#define COMMANDS
//#include "Joystick.h"

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

#define RELEASE_POKEMON_MACRO\
        { NOTHING,  150 },/*Select Pokemon*/\
		{ A,          5 },\
		{ NOTHING,  150 },/*Select 'Release'*/\
		{ UP,         5 },\
		{ NOTHING,  150 },\
		{ UP,         5 },\
		{ NOTHING,  150 },\
		{ A,          5 },\
		{ NOTHING,  150 },/*Are we sure?*/\
		{ UP,         5 },\
		{ NOTHING,  150 },\
		{ A,          5 },\
        { NOTHING,  150 }
static const command_set Release_Entire_Box = {
	false, //Repeat
	{
		// First row
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,

		// Second row
		{ DOWN,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,

		// Third row
		{ DOWN,       5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,

		// Forth row
		{ DOWN,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,
		{ LEFT,       5 },
		RELEASE_POKEMON_MACRO,

		// Fith row
		{ DOWN,       5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO,
		{ RIGHT,      5 },
		RELEASE_POKEMON_MACRO
	}
};

#endif