#include "utilities.h"

void processButton(buttonInfo_t* button) {           //Procesar estado actual del boton
	switch (button->button_state) {
		case STATE_BUTTON_UP:
			if (!button->reading_func(button->button)) {
				button->button_state = STATE_BUTTON_FALLING;
			}
			break;

		case STATE_BUTTON_DOWN:
			/* CHECK TRANSITION CONDITIONS */
			if (button->reading_func(button->button)) {
				button->button_state = STATE_BUTTON_RISING;
			}
			break;

		case STATE_BUTTON_FALLING:
			/* ENTRY */
			if (button->flag_falling == 0) {
				button->flag_falling = 1;
				break;
			}
			/* CHECK TRANSITION CONDITIONS */
			if (!button->reading_func(button->button)) {
				button->button_state = STATE_BUTTON_DOWN;
				button->falling_info.action(
						button->falling_info.outputDirectionOrFlag,
						button->falling_info.outputData);
				printf("F\r\n");
			} else {
				button->button_state = STATE_BUTTON_UP;
			}
			/* LEAVE */
			if (button->button_state != STATE_BUTTON_FALLING) {
				button->flag_falling = 0;
			}
			break;
		case STATE_BUTTON_RISING:
			/* ENTRY */
			if (button->flag_rising == 0) {
				button->flag_rising = 1;
				break;
			}
			/* CHECK TRANSITION CONDITIONS */
			if (button->reading_func(button->button)) {
				button->button_state = STATE_BUTTON_UP;
				button->rising_info.action(
						button->rising_info.outputDirectionOrFlag,
						button->rising_info.outputData);
			} else {
				button->button_state = STATE_BUTTON_DOWN;
			}

			/* LEAVE */
			if (button->button_state != STATE_BUTTON_RISING) {
				button->flag_rising = 0;
				break;
			}
		default:
			break;

	}
}
