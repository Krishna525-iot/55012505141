#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
//#include "globals.h"
//#include "lcd.h"
//#include "command_manager.h"

#define INPUT_QUEUE_SIZE 1

typedef enum {
	INPUT_SOURCE_BUTTON, INPUT_SOURCE_GESTURE, INPUT_SOURCE_UART
} InputSource;

typedef enum {
	INPUT_INC, // 0
	INPUT_NW, // 1
	INPUT_WW, //2
	INPUT_DCR, //3
	INPUT_TOGGLE, //4
	INPUT_CW,
	INPUT_NW_off, // 1
	INPUT_WW_off, //
	INPUT_TOGGLE_off, //4
	led_off,
	led_on,
	INPUT_CW_off,
	 INPUT_NW_LONG,
	 INPUT_WW_LONG,
	 INPUT_CW_LONG,
	 INPUT_DCR_LONG,
	 INPUT_INC_LONG,
	 INPUT_TOGGLE_LONG,           // New short press action for DEPTH button
	 INPUT_UNKNOWN = -1,
} InputAction;


//typedef enum {
//	 INPUT_NW, // 1
//	 INPUT_WW, // 2
//	 INPUT_CW, // 6
//	 INPUT_DCR, // 3
//	 INPUT_INC, // 0
//	 INPUT_TOGGLE, // 4
//	 INPUT_NW_LONG,
//	 INPUT_WW_LONG,
//	 INPUT_CW_LONG,
//	 INPUT_DCR_LONG,
//	 INPUT_INC_LONG,
//	 INPUT_TOGGLE_LONG,           // New short press action for DEPTH button
//	 INPUT_UNKNOWN = -1,
//} InputAction;


typedef struct {
	InputSource source; // INPUT_SOURCE_BUTTON, INPUT_SOURCE_GESTURE, etc.
	InputAction action; // INPUT_MOVE_UP, INPUT_MOVE_DOWN, INPUT_SELECT, etc.
} InputEvent;

typedef struct {
	InputEvent events[INPUT_QUEUE_SIZE];
	uint8_t head;
	uint8_t tail;
} InputQueue;

// Function Prototypes
void enqueue_event(InputEvent event);
int dequeue_event(InputEvent *event);
void handle_input(InputAction action);
void process_input_events(void);
void handle_button_input(void);


#endif // INPUT_MANAGER_H
