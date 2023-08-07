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
		{ NOTHING, 500 }
	}
};

static const command_set Sync_Controller = {
	false, // Repeat
	9, // Command count
	{
		{ A,          5 },
		{ NOTHING,  500 },
		{ TRIGGERS,   5 },
		{ NOTHING,  250 },
		{ TRIGGERS,   5 },
		{ NOTHING,  250 },
		{ TRIGGERS,   5 },
		{ NOTHING,  250 },
		{ A,          5 }
	}
};

static const command_set AntiAFK = {
	true, // Repeat
	8,
	{
		{ NOTHING, 100 },
		{ RS_UP,   100 },
		{ NOTHING, 100 },
		{ LS_DOWN, 100 },
		{ NOTHING, 100 },
		{ LS_UP,   100 },
		{ NOTHING, 100 },
		{ RS_DOWN, 100 }
	}
};

#endif