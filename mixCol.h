//#include "specialMath.h"
void MixColumns(char state[STATE_SIZE]){
	/*
	 * This matrix is defined specifically by rijndael.
	 * */
        const unsigned int mc_constant[STATE_SIZE] =
        {
                0x02, 0x03, 0x01, 0x01,
                0x01, 0x02, 0x03, 0x01,
                0x01, 0x01, 0x02, 0x03,
                0x03, 0x01, 0x01, 0x02
        };

	unsigned int _state[STATE_SIZE];

	for(int i=0; i<STATE_SIZE; i++){
		_state[i] = (state[i] & 0xf0)+(state[i] & 0x0f);
	}

        for(int i=0; i<4; i++){
                for(int k=0; k<4; k++){
                        unsigned int ret = 0x0;
                        for(int l=0; l<4; l++){
                                ret = ret ^ galoisMultiply(mc_constant[(k*4)+l], _state[(i*4)+l]);
                        }
                        state[(i*4)+k] = ret;
                }
        }
}

void inv_MixColumns(char state[STATE_SIZE]){
        const unsigned int mc_constant[STATE_SIZE] =
        {
                0x0e, 0x0b, 0x0d, 0x09,
                0x09, 0x0e, 0x0b, 0x0d,
                0x0d, 0x09, 0x0e, 0x0b,
                0x0b, 0x0d, 0x09, 0x0e
        };

	unsigned int _state[STATE_SIZE];
	for(int i=0; i<STATE_SIZE; i++){
		_state[i] = (state[i] & 0xf0)+(state[i] & 0x0f);
	}

        for(int i=0; i<4; i++){
                for(int k=0; k<4; k++){
                        unsigned int ret = 0x0;
                        for(int l=0; l<4; l++){
                                ret = ret ^ galoisMultiply(mc_constant[(k*4)+l], _state[(i*4)+l]);
                        }
                        state[(i*4)+k] = ret;
                }
        }
}
