/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
	(C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
	(C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

#include "Joystick.h"
#include "Commands.h"

command_set current_command_set;

typedef enum {
	STANDBY,
	CONNECTING,
	AFK
} State_t;
State_t state = STANDBY;

void SetLed(bool on)
{
	if (on)
		PORTD |= (1 << PD6);
	else
		PORTD &= ~(1 << PD6);
}
void ToggleLed()
{
	PORTD ^= (1 << PD6);
}

// Main entry point.
int main(void) {
	// Turn on LED on pin D6
	DDRD |= (1 << DDD6);

	current_command_set = Sync_Controller;

	// We'll start by performing hardware and peripheral setup.
	SetupHardware();
	// We'll then enable global interrupts for our use.
	GlobalInterruptEnable();
	// Once that's done, we'll enter an infinite loop.
	for (;;)
	{
		// We need to run our task to process and deliver data for our IN and OUT endpoints.
		HID_Task();
		// We also need to run the main USB management task.
		USB_USBTask();

		// Toggle built-in led to show we're alive and well
		ToggleLed();
	}
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void) {
	// We need to disable watchdog if enabled by bootloader/fuses.
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// We need to disable clock division before initializing the USB hardware.
	clock_prescale_set(clock_div_1);
	// We can then initialize our hardware and peripherals, including the USB stack.

	// The USB stack should be initialized last.
	USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void) {
	// We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void) {
	// We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void) {
	bool ConfigSuccess = true;

	// We setup the HID report endpoints.
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

	// We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void) {
	// We can handle two control requests: a GetReport and a SetReport.

	// Not used here, it looks like we don't receive control request from the Switch.
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void) {
	// If the device isn't connected and properly configured, we can't do anything here.
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;

	// We'll start with the OUT endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
	// We'll check to see if we received something on the OUT endpoint.
	if (Endpoint_IsOUTReceived())
	{
		// If we did, and the packet has data, we'll react to it.
		if (Endpoint_IsReadWriteAllowed())
		{
			// We'll create a place to store our data received from the host.
			USB_JoystickReport_Output_t JoystickOutputData;
			// We'll then take in that data, setting it up in our storage.
			while(Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError);
			// At this point, we can react to this data.

			// However, since we're not doing anything with this data, we abandon it.
		}
		// Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
		Endpoint_ClearOUT();
	}

	// We'll then move on to the IN endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
	// We first check to see if the host is ready to accept data.
	if (Endpoint_IsINReady())
	{
		// We'll create an empty report.
		USB_JoystickReport_Input_t JoystickInputData;
		// We'll then populate this report with what we want to send to the host.
		GetNextReport(&JoystickInputData);
		// Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
		while(Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError);
		// We then send an IN packet on this endpoint.
		Endpoint_ClearIN();
	}
}

#define ECHOES 2
int echoes = 0;
USB_JoystickReport_Input_t last_report;

int bufindex = 0;
int duration_count = 0;

bool breakCommand = false;

void PrepareData(USB_JoystickReport_Input_t* const ReportData, Buttons_t button)
{
	switch (button)
	{
		// DPAD
		case UP:
			ReportData->HAT = HAT_TOP;
			break;
		case UP_LEFT:
			ReportData->HAT = HAT_TOP_LEFT;
			break;
		case UP_RIGHT:
			ReportData->HAT = HAT_TOP_RIGHT;
			break;
		case DOWN:
			ReportData->HAT = HAT_BOTTOM;
			break;
		case DOWN_LEFT:
			ReportData->HAT = HAT_BOTTOM_LEFT;
			break;
		case DOWN_RIGHT:
			ReportData->HAT = HAT_BOTTOM_RIGHT;
			break;
		case LEFT:
			ReportData->HAT = HAT_LEFT;
			break;
		case RIGHT:
			ReportData->HAT = HAT_RIGHT;
			break;

		// LEFT STICK
		case LS_UP:
			ReportData->LY = STICK_MIN;				
			break;
		case LS_LEFT:
			ReportData->LX = STICK_MIN;				
			break;
		case LS_DOWN:
			ReportData->LY = STICK_MAX;				
			break;
		case LS_RIGHT:
			ReportData->LX = STICK_MAX;				
			break;
		case LS_CLICK:
			ReportData->Button |= SWITCH_LCLICK;
			break;

		// RIGHT STICK
		case RS_UP:
			ReportData->RY = STICK_MIN;				
			break;
		case RS_LEFT:
			ReportData->RX = STICK_MIN;				
			break;
		case RS_DOWN:
			ReportData->RY = STICK_MAX;				
			break;
		case RS_RIGHT:
			ReportData->RX = STICK_MAX;				
			break;
		case RS_CLICK:
			ReportData->Button |= SWITCH_RCLICK;
			break;

		// FACE BUTTONS
		case A:
			ReportData->Button |= SWITCH_A;
			break;
		case B:
			ReportData->Button |= SWITCH_B;
			break;
		case X:
			ReportData->Button |= SWITCH_X;
			break;
		case Y:
			ReportData->Button |= SWITCH_Y;
			break;
		case PLUS:
			ReportData->Button |= SWITCH_PLUS;
			break;
		case MINUS:
			ReportData->Button |= SWITCH_MINUS;
			break;
		
		// TRIGGERS AND SHOULDERS
		case L:
			ReportData->Button |= SWITCH_L;
			break;
		case R:
			ReportData->Button |= SWITCH_R;
			break;
		case ZL:
			ReportData->Button |= SWITCH_ZL;
			break;
		case ZR:
			ReportData->Button |= SWITCH_ZR;
			break;
		case TRIGGERS:
			ReportData->Button |= SWITCH_L | SWITCH_R;
			break;
		
		case HOME:
			ReportData->Button |= SWITCH_HOME;
			break;

		// NO BUTTONS
		default:
			ReportData->LX = STICK_CENTER;
			ReportData->LY = STICK_CENTER;
			ReportData->RX = STICK_CENTER;
			ReportData->RY = STICK_CENTER;
			ReportData->HAT = HAT_CENTER;
			break;
	}
}

// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t* const ReportData) {

	// Prepare an empty report
	memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
	ReportData->LX = STICK_CENTER;
	ReportData->LY = STICK_CENTER;
	ReportData->RX = STICK_CENTER;
	ReportData->RY = STICK_CENTER;
	ReportData->HAT = HAT_CENTER;

	// Repeat ECHOES times the last report
	if (echoes > 0)
	{
		memcpy(ReportData, &last_report, sizeof(USB_JoystickReport_Input_t));
		echoes--;
		return;
	}

	PrepareData(ReportData, current_command_set.commands[bufindex].button);

	duration_count++;

	if (duration_count > current_command_set.commands[bufindex].duration)
	{
		bufindex++;
		duration_count = 0;				
	}


	if (bufindex >= current_command_set.command_count)
	{
		
		bufindex = 0;
		duration_count = 0;
		// If current command set does not repeat, go to next state
		if (!current_command_set.repeats)
		{
			switch(state)
			{
				case STANDBY:
					state = CONNECTING;
					current_command_set = Sync_Controller;
					break;
				case CONNECTING:
					state = AFK;
					current_command_set = AntiAFK;
					break;
				case AFK:
					state = STANDBY;
					current_command_set = NULL_COMMAND_SET;
					break;
			}
		}
	}

	// Prepare to echo this report
	memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
	echoes = ECHOES;

}
