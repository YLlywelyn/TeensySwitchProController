## Switch Controller Emulator

A switch pro controller emulator that uses a Teensy 2.0.  The planned use case for this particular emulator is to avoid being kicked from Minecraft Realms for being AFK, allowing my auto farms to actually work.

### Steps

1. Connect the Teensy to the switch dock
2. Have the game running and dock the switch
3. The game complains about each player needing a controller.  Press `A`.
4. The switch controller settings page opens. Press `L+R` several times, followed by `A`.
5. We should now be ready to AFK.

### Controller States

This controller emulator has a few states that it goes through 

1. `STANDBY`
	: Wait a few seconds for the switch to connect to the dock
2. `CONNECTING`
	- Press `A`
	- Wait a few seconds
	- Spam `L+R` several times
	- Press `A` again
3. `AFK`
	: Repeat a sequence of commands to beat the AFK detection

### TODO

- 
