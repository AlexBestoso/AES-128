//#include "specialMath.h"

/*
 * Imgine the state as a 4 by 4 matrix
 * */

void ShiftRows(char state[STATE_SIZE]){
        char _state[STATE_SIZE];
        unsigned int shiftAmount;

        for(int i=0; i<STATE_SIZE; i++){
                shiftAmount = mod(0-i, 4);
                _state[mod(i+(shiftAmount*4), STATE_SIZE)] = state[i];
        }

        for(int i=0; i<STATE_SIZE; i++)
                state[i] = _state[i];
}

void inv_ShiftRows(char state[STATE_SIZE]){
        char _state[STATE_SIZE];
        int shiftAmount;

        for(int i=0; i<STATE_SIZE; i++){
                shiftAmount = mod(0-i, 4);
                _state[mod(i-(shiftAmount*4), STATE_SIZE)] = state[i];
        }

        for(int i=0; i<STATE_SIZE; i++)
                state[i] = _state[i];
}
