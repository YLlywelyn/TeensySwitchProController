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

#endif