#ifndef COMMANDS
#define COMMANDS

typedef enum {
	NOTHING,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
	LS_UP,
	LS_DOWN,
	LS_LEFT,
	LS_RIGHT,
	LS_CLICK,
	RS_UP,
	RS_DOWN,
	RS_LEFT,
	RS_RIGHT,
	RS_CLICK,
	A,
	B,
	X,
	Y,
	L,
	R,
	ZL,
	ZR,
	PLUS,
	MINUS,
	HOME,
	TRIGGERS
} Buttons_t;

typedef struct {
	Buttons_t button;
	uint16_t duration;
} command;

typedef struct {
	bool repeats;
	uint16_t command_count;
	command commands[];
} command_set;

bool CompareCommandSets(command_set a, command_set b)
{
	return (a.repeats == b.repeats && a.commands == b.commands);
}

static const command_set NULL_COMMAND_SET = {
	false, // Repeat
	1, // Command count
	{
		{ NOTHING, 1 }
	}
};

static const command_set TEST_COMMANDS = {
	false,
	72,
	{
		{ NOTHING,  500 },
		{ TRIGGERS,   5 },
		{ NOTHING,  150 },
		{ TRIGGERS,   5 },
		{ NOTHING,  150 },
		{ TRIGGERS,   5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  500 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
		{ NOTHING,  150 },
		{ A,          5 },
	}
};

static const command_set Sync_Controller = {
	false, // Repeat
	7, // Command count
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
	2, // Command count
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
	419, // Command count
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