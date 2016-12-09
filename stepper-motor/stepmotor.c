/*
 * step_motor.c
 *
 * Created: 23.11.2016 19:03:57
 *  Author: marek
 */ 
#include "stepmotor.h"


void lengtht_toStep(STEPPER_OBJECT *_obj){
 
 _obj->distance_step_counter=((_obj->distance)/ONEROTATION_LENGTH)*ONEROTATION_TOSTEP;

}
STEPMOTOR_PROCESS_STATE STEPMOTOR_getState(STEPPER_OBJECT* _obj){
	return _obj->internalState;
}


STEPPER_INFO STEPMOTOR_move_forward(STEPPER_OBJECT *_obj, uint16_t distance, uint8_t speed){
 _obj->distance = distance;
 _obj->speed	= speed;
if(_obj->internalState == MOVE_BACKWORDS_STATE){
return ROTATION_ERROR;
}else{
_obj->internalState = MOVE_FORWARD_STATE;
return ROTATION_RUN;
}

}

STEPPER_INFO STEPMOTOR_move_backwards(STEPPER_OBJECT *_obj, uint16_t distance, uint8_t speed){
	_obj->distance = distance;
	_obj->speed	= speed;
	if(_obj->internalState == MOVE_FORWARD_STATE){
		return ROTATION_ERROR;
		}else{
		_obj->internalState = MOVE_BACKWORDS_STATE;
		return ROTATION_RUN;
	}
}

STEPPER_INFO STEPMOTOR_PROCESS(STEPPER_OBJECT *_obj){

}


}