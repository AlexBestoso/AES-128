/*
 * These Headers are Required for 
 * AES_128_Raw to work
 */
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "specialMath.h"
#include "mixCol.h"
#include "shiftRow.h"
#include "aesSbox.h"
#include "keySched.h"
#include "aes.h"

/*
 * This header is just for the 
 * sample implementation
 */
#include <stdio.h>

int main(void){
	/*
	 * All the AES functions were designed
	 * to encipher strings of data, meaning
	 * that all the arrys you use with this
	 * implementation must be null terminated
	 */
	size_t ExpandedKeySize = (16*(10+1))+1;
	char expandedKey[ExpandedKeySize];

	char state[16] = "0123456789abcdef";
	char key[16]   = "fedcba9876543210";
	/*
	 * This second key is used because the
	 * functions used in this algorithm
	 * zero out the key buffer.
	 */
	char key2[16]  = "fedcba9876543210";

	/*
	 * Enjoy :-)
	 */

	printf("Pre Encipher : ");
	for(int i=0; i<STATE_SIZE; i++){
		printf("%X ", state[i]);
	}printf("\n");

	aes_128_encipher(state, key);

	printf("Post Encipher/Pre Decipher : ");
	for(int i=0; i<STATE_SIZE; i++){
                printf("%X ", state[i]);
        }printf("\n");	
	
	aes_128_decipher(state, key2);
	printf("\nPost Decipher : ");
	for(int i=0; i<STATE_SIZE; i++){
                printf("%X ", state[i]);
        }printf("\n");
	return 0;
}
/*
 * This implementation is assumed to be broken
 * as it's unoffical. Please use implemntations,
 * which are accepted for use by NIST.
 */
