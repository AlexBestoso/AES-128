/*
 * These Headers are Required for 
 * AES_128_Raw to work
 */
#include <math.h>
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

	char state[17] = "0123456789abcdef\0";
	char key[17]   = "fedcba9876543210\0";
	/*
	 * This second key is used because the
	 * functions used in this algorithm
	 * zero out the key buffer.
	 */
	char key2[17]  = "fedcba9876543210\0";

	/*
	 * Enjoy :-)
	 */

	printf("Pre Encipher  : %s\n", state);
	aes_128_encipher(state, key);

	printf("Post Encipher/Pre Decipher  : %s\n", state);	
	
	aes_128_decipher(state, key2);
	printf("\nPost Decipher : %s\n", state);
	return 0;
}
/*
 * This implementation is assumed to be broken
 * as it's unoffical. Please use implemntations,
 * which are accepted for use by NIST.
 */
