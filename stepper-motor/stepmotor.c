/*
 * step_motor.c
 *
 * Created: 23.11.2016 19:03:57
 *  Author: marek
 */ 
#include "stepmotor.h"

STEPPER_INFO STEPMOTOR_INIT(STEPPER_OBJECT *_obj){
	_obj->coil_switch_counter = 0;
	_obj->distance = 0;
	_obj->distance_step_counter = 0;
	_obj->internalState = INIT;
	_obj->steps_counter = 0;
	_obj->speed = 0;
	_obj->delay = 0;
	
}

void lengtht_toStep(STEPPER_OBJECT *_obj){
 
 _obj->distance_step_counter=((_obj->distance)/ONEROTATION_LENGTH)*ONEROTATION_TOSTEP;

}
STEPMOTOR_PROCESS_STATE STEPMOTOR_getState(STEPPER_OBJECT* _obj){
	return _obj->internalState;
}


STEPPER_INFO STEPMOTOR_move_forward(STEPPER_OBJECT *_obj, uint16_t distance, uint16_t speed){
 _obj->distance = distance;
 _obj->speed	= speed;
_obj->coil_switch_counter = 0;
_obj->internalState = MOVE_FORWARD_STATE;


}

STEPPER_INFO STEPMOTOR_move_backwards(STEPPER_OBJECT *_obj, uint16_t distance, uint16_t speed){
	_obj->distance = distance;
	_obj->speed	= speed;
	_obj->coil_switch_counter = 0;
	_obj->internalState = MOVE_BACKWORDS_STATE;
	//if(_obj->internalState == MOVE_FORWARD_STATE){
		//return ROTATION_ERROR;
		//}else{
		//_obj->internalState = MOVE_BACKWORDS_STATE;
		//return ROTATION_RUN;
	//}
}

STEPPER_INFO STEPMOTOR_PROCESS(STEPPER_OBJECT *_obj){
	
	if (_obj->delay > 0){
		_obj->delay--;
		if(_obj->delay > 0)
		return ROTATION_ERROR;
	}
	if (_obj->coil_switch_counter==8){
		_obj->coil_switch_counter = 0;
	}
	switch(_obj->internalState) {
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
}


