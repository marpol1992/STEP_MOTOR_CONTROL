/*
 * step_motor.h
 *
 * Created: 23.11.2016 19:03:32
 *  Author: marek
 */ 


#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#define TEST_GL	PORTE.OUTTGL = PIN0_bm
#define MOTOR_PIN1_ON	PORTE.OUTSET = PIN1_bm
#define MOTOR_PIN2_ON	PORTE.OUTSET = PIN2_bm
#define MOTOR_PIN3_ON   PORTE.OUTSET = PIN3_bm
#define MOTOR_PIN4_ON   PORTE.OUTSET = PIN4_bm

#define MOTOR_PIN1_OFF  PORTE.OUTCLR = PIN1_bm
#define MOTOR_PIN2_OFF	PORTE.OUTCLR = PIN2_bm
#define MOTOR_PIN3_OFF	PORTE.OUTCLR = PIN3_bm
#define MOTOR_PIN4_OFF	PORTE.OUTCLR = PIN4_bm

#define ONEROTATION_TOSTEP 50
#define ONEROTATION_LENGTH 5  //how far screw move on One rotation motor [mm]

typedef enum{
	ROTATION_DONE = -1,
	ROTATION_ERROR = 0,
	ROTATION_RUN,
}	STEPPER_INFO;

typedef enum{
	MOVE_FORWARD_STATE = 0,
	MOVE_BACKWORDS_STATE,
	MOVE_FORWARD_FINISH,
	MOVE_BACKWORDS_FINISH,
}STEPMOTOR_PROCESS_STATE;

typedef struct{
	uint8_t speed;
	uint16_t distance;
	uint32_t steps_counter;
	uint32_t distance_step_counter;
	uint8_t  coil_switch_counter;
	STEPMOTOR_PROCESS_STATE internalState;

}STEPPER_OBJECT;

STEPPER_INFO STEPMOTOR_move_forward(STEPPER_OBJECT *_obj, uint16_t distance, uint8_t speed);
STEPPER_INFO STEPMOTOR_move_backwards(STEPPER_OBJECT *_obj, uint16_t distance, uint8_t speed);
STEPPER_INFO STEPMOTOR_PROCESS(STEPPER_OBJECT *_obj);

STEPMOTOR_PROCESS_STATE STEPMOTOR_getState(STEPPER_OBJECT* _obj);
void lenght_toStep(STEPPER_OBJECT *_obj);


#endif /* STEPMOTOR_H_ */