## Switch Controller Emulator

A switch pro controller emulator that uses a Teensy 2.0, a couple of buttons and a small display to allow for multiple repeatable command strings to be sent to a conected switch.

### TODO

- To break repeating command sets with a button press, set `state` to `CLEANUP`

### Controller States

1. `BREATHE`
	: Wait for a command set to be selected then goto `PROCESS`
2. `PROCESS`
	: Run through the current command set then, if it does not repeat, go to `CLEANUP`, if it does, restart it
3. `CLEANUP`
	: Reset all state variables and go back to `BREATHE`