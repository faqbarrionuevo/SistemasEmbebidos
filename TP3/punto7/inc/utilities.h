#ifndef EXAMPLES_C_PROJECTS_TP3_UTILITIES_H_
#define EXAMPLES_C_PROJECTS_TP3_UTILITIES_H_

#include <stdio.h>

#include "myGpio.h"

// Enums, structs, and types

typedef uint8_t bool_t;

typedef enum {
	STATE_BUTTON_UP,
	STATE_BUTTON_DOWN,
	STATE_BUTTON_FALLING,
	STATE_BUTTON_RISING
} buttonState_t;

// Function pointer to a routine to execute if button is executed
// The first parameter is associated to a context variable (i.e. provides information about where to send the signal)
// The second parameter tells the information to send to the output
typedef void (*onButtonPressed_func)(uint8_t, uint8_t);

// Function pointer to a routine to execute if button is executed
// The first parameter is associated to a context variable (i.e. provides information about where to read the signal from)
typedef bool_t (*checkButtonPressed_func)(uint8_t);


// Struct util to generalize sending output data
typedef struct {
	// Output pin/info/flag
	uint8_t outputDirectionOrFlag;
	// Data to send to the output
	uint8_t outputData;
	// Action to execute if button is pressed
	onButtonPressed_func action;
} buttonOutputData_t;

typedef struct {
	buttonState_t button_state;
	bool_t flag_falling;
	bool_t flag_rising;
	myGpioMap_t button;
	buttonOutputData_t falling_info;
	buttonOutputData_t rising_info;
	checkButtonPressed_func reading_func;
} buttonInfo_t;


// Functions

void processButton(buttonInfo_t* button);

#endif // EXAMPLES_C_PROJECTS_TP3_UTILITIES_H_
