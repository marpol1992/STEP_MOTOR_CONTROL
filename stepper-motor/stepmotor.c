/****************************************************************
 * step_motor.c
 *
 * Created: 23.11.2016 19:03:57
 *  Author: MAREK WUDARCZYK
 ****************************************************************/ 
#include "stepmotor.h"

/****************************************************************
*
* FUNCTION INITIAL STEP MOTOR
* input: object STEPPERT_OBJECT
* output: info with STEPPER_INFO
*
*****************************************************************/
STEPPER_INFO STEPMOTOR_INIT(STEPPER_OBJECT *_obj){
	_obj->coil_switch_counter = 0;
	_obj->distance = 0;
	_obj->distance_step_counter = 0;
	_obj->internalState = INIT;
	_obj->steps_counter = 0;
	_obj->speed = 0;
	_obj->delay = 0;
	return ROTATION_DONE;
}

/****************************************************************
*
* FUNCTION CONVERT LENGHT TO STEP
* input: object STEPPERT_OBJECT
* output: PROCESS_OK
*
*****************************************************************/
STEPPER_INFO lenght_toStep(STEPPER_OBJECT *_obj){
 
	_obj->distance_step_counter=((_obj->distance)/ONEROTATION_LENGTH)*ONEROTATION_TOSTEP;
	return PROCESS_OK;
}
STEPMOTOR_PROCESS_STATE STEPMOTOR_getState(STEPPER_OBJECT *_obj){
	return _obj->internalState;
}

/****************************************************************
*
* FUNCTION MOVET MOTOR TO FORWARD
* input: STEPPER_OBJECT *_obj, uint16_t distance, uint16_t speed
* output: ROTATION_DONE or ROTATION_RUN
*
*****************************************************************/
STEPPER_INFO STEPMOTOR_move_forward(STEPPER_OBJECT *_obj, uint16_t distance, uint16_t speed){
	if((_obj->internalState == MOVE_FORWARD_FINISH) | (_obj->internalState == INIT)  | (_obj->internalState == MOVE_BACKWORDS_STATE) |  (_obj->internalState == MOVE_BACKWORDS_FINISH)){ //opcja czekania az skonczy sie jaki kolwiek ruch, ma byc mozliwosc zmiany kierunku bez wplywu na zakonczenie obrotu
	_obj->distance = distance;
	_obj->speed	= speed;
	_obj->coil_switch_counter = 0;
	if(lenght_toStep(_obj));
	_obj->internalState = MOVE_FORWARD_STATE;
	_obj->steps_counter = 0;
	ENA_ON;
	ENB_ON;
	return ROTATION_DONE;
	}else return ROTATION_RUN;
}
/****************************************************************
*
* FUNCTION MOVET MOTOR TO BACWARD
* input: STEPPER_OBJECT *_obj, uint16_t distance, uint16_t speed
* output: ROTATION_DONE OR ROTATION_RUN
*
*****************************************************************/
STEPPER_INFO STEPMOTOR_move_backwards(STEPPER_OBJECT *_obj, uint16_t distance, uint16_t speed){
	if((_obj->internalState == MOVE_BACKWORDS_FINISH) | (_obj->internalState == INIT)  | (_obj->internalState == MOVE_FORWARD_STATE) | (_obj->internalState == MOVE_FORWARD_FINISH)){
	_obj->distance = distance;
	_obj->speed	= speed;
	_obj->coil_switch_counter = 0;
	lenght_toStep(_obj);
	_obj->internalState = MOVE_BACKWORDS_STATE;
	_obj->steps_counter = 0;
	ENA_ON;
	ENB_ON;
	return ROTATION_DONE;
	}else
	return ROTATION_RUN;
}

/****************************************************************
*
* MAIN FUNCTION CHANGE COIL IN MOTOR, FORWARD OR BACKWORD
* input: STEPPER_OBJECT *_obj, 
* output: ROTATION_ERROR OR ROTATION_RUN
*
*****************************************************************/
STEPPER_INFO STEPMOTOR_PROCESS(STEPPER_OBJECT *_obj){
	
	if (_obj->delay > 0){
		_obj->delay--;
		if(_obj->delay > 0)
		return ROTATION_ERROR;
	}
	if (_obj->coil_switch_counter==8){
		_obj->coil_switch_counter = 0;
	}
	
	if (_obj->steps_counter == _obj->distance_step_counter){
		if (_obj->internalState == MOVE_FORWARD_STATE){
		_obj->internalState = MOVE_FORWARD_FINISH;
		}else{
			_obj->internalState = MOVE_BACKWORDS_FINISH;
		}
		
	}
	_obj->steps_counter++;
	
	switch(_obj->internalState){
		case MOVE_BACKWORDS_FINISH:
		case MOVE_FORWARD_FINISH:
			MOTOR_PIN1_OFF;
			MOTOR_PIN2_OFF;
			MOTOR_PIN3_OFF;
			MOTOR_PIN4_OFF;
			return ROTATION_DONE;
		case MOVE_FORWARD_STATE:
		_obj->coil_switch_counter++;
			switch(_obj->coil_switch_counter){
				case 1:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_OFF;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_OFF;
					_obj->delay = _obj->speed;
					break;
				}
				case 2:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_OFF;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 3:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_OFF;
					MOTOR_PIN3_OFF;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 4:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_OFF;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 5:{
					MOTOR_PIN1_OFF;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_OFF;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 6:{
					MOTOR_PIN1_OFF;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 7:{
					MOTOR_PIN1_OFF;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_OFF;
					_obj->delay = _obj->speed;
					break;
				}
				case 8:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_OFF;
					_obj->delay = _obj->speed;
					break;
				}
				default:{
					break;
				}
			}
		 break;
		
		case MOVE_BACKWORDS_STATE:
		_obj->coil_switch_counter++;
			switch(_obj->coil_switch_counter){
				case 1:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_OFF;
					_obj->delay = _obj->speed;
					break;
				}
				case 2:{
					MOTOR_PIN1_OFF;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_OFF;
					_obj->delay = _obj->speed;
					break;
				}
				case 3:{
					MOTOR_PIN1_OFF;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 4:{
					MOTOR_PIN1_OFF;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_OFF;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 5:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_ON;
					MOTOR_PIN3_OFF;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 6:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_OFF;
					MOTOR_PIN3_OFF;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 7:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_OFF;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_ON;
					_obj->delay = _obj->speed;
					break;
				}
				case 8:{
					MOTOR_PIN1_ON;
					MOTOR_PIN2_OFF;
					MOTOR_PIN3_ON;
					MOTOR_PIN4_OFF;
					_obj->delay = _obj->speed;
					break;
				}
			}
		break;	
	
	}
	return ROTATION_RUN;
}


