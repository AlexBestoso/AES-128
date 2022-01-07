#include "aes128.h"

/*
 * This header is just for the 
 * sample implementation
 */
#include <stdio.h>

int main(void){
	char message[16];strncpy(message, "0123456789abcdef", STATE_SIZE);
	char key[16]; strncpy(key, "fedcba9876543210", KEY_SIZE);
	/*
	 * This second key is used because the
	 * functions used in this algorithm
	 * zero out the key buffer.
	 */
	char key2[16]; strncpy(key2, "fedcba9876543210", KEY_SIZE);

	AES_128 aes;

	/*
	 * Enjoy :-)
	 */

	printf("Pre Encipher : ");
	for(int i=0; i<STATE_SIZE; i++){
		printf("%X ", message[i]);
	}printf("\n");

	aes.encipher(message, key);

	printf("Post Encipher/Pre Decipher : ");
	for(int i=0; i<STATE_SIZE; i++){
                printf("%X ", message[i]);
        }printf("\n");	
	
	aes.decipher(message, key2);
	printf("\nPost Decipher : ");
	for(int i=0; i<STATE_SIZE; i++){
                printf("%X ", message[i]);
        }printf("\n");
	return 0;
}
/*
 * This implementation is assumed to be broken
 * as it's unoffical. Please use implemntations,
 * which are accepted for use by NIST.
 */
