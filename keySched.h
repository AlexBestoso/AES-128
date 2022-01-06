/*
 * Standard ROT permutation. Essentailly caesar with a left shift of 1.
 * */
void ROT_Word(char word[4]){
        char tmp[4];
        for(int i=0; i<4; i++){
                tmp[mod((i-1), 4)] = word[i];
        }
        for(int i=0; i<4; i++){
                word[i] = tmp[i];
        }
}

/*
 * Round needs to be subtracted by one when it's passed into the OG function
 * This function gets a value that adds greater security to the key expansion process.
 */
char getRoundCoeff(int round){
        int test = pow(2, round);
        char ret;
	/*
	 * If the value is greater than GF(2⁸), reduce the value until it's 8 bits in size.  
	 * */
        if(test > 256){
		// 0x11b is an irreducable polynomial value specified by rijndael.
                test = galoisMod(test, 0x11b);
                ret = (char)test;
                return ret;
        }
        ret = (char)test;
        return ret;
}

/*
 * A custom permutiation for key expansion defined by rijndael.
 * */
void OG(int round, char word[4]){
        char RC;
        ROT_Word(word);
        for(int i=0; i<4; i++){
                word[i] = sBox(word[i]);
        }
        RC = getRoundCoeff(round);
        word[0] = word[0] ^ RC;
}

/*
 * The process to key expansion is similar to Cipher Block Chaining. Where you use the 
 * first chunk of data as padding for the next following chunk of data.
 * */
void expandKey_128(char key[KEY_SIZE], char expandedKey[KEY_SIZE * (ROUND_COUNT+1)]){
        char word[4];
        int round = 0;

	/*
	 * Place Key into expanded Key Buffer. Call this round one.
	 * */
	memset(expandedKey, 0x00, KEY_SIZE * (ROUND_COUNT+1));
        for(int i=0; i<KEY_SIZE; i++){
                expandedKey[i] = key[i];
        }
        /* 
	 * nullify the key array to reduce the amount of 
	 * sensitive bytes in memory.
	 * */
	memset(key, 0x00, KEY_SIZE);
        round++;

	/*
	 * Now Actually Expand The Key!
	 * */
        for(int i=0; i<ROUND_COUNT; i++){
		char _key[KEY_SIZE];
		
		/* Take the a KEY_SIZE chunk of data from the expanded key.
		 * The math equation states, take the first (round-1) KEY_SIZE block of bytes
		 * And populate the key buffer with them.*/
                for(int j=0; j<KEY_SIZE; j++){
                        _key[j] = expandedKey[((round-1)*KEY_SIZE)+j];
                }

		/*
		 * take the last 4 bytes out of our key buffer
		 * */
                for(int j=KEY_SIZE-4; j<KEY_SIZE; j++){
                        word[j%4] = _key[j];
                }

		/*
		 * Do OG Magical Operations.
		 * */
                OG(round-1, word);

		/*
		 * Take the modified word variable and XOR each value with the 
		 * first 4 bytes of the key buffer. Storing the resulting value in the next block 
		 * of the expanded key. If the earlier loops took the first 16 bytes of the expanded key array,
		 * this loop places the first 4 bytes into of the next 16 bytes.
		 * */
                for(int j=0; j<4; j++){
                        expandedKey[(round*KEY_SIZE)+j] = key[j] ^ word[j];
                }

		/*
		 * We now xor the remainder of the key with the expansion key. Where the iterator value 
		 * of the expanded key is -4, the size of the word variable, from the current position.
		 * */
                for(int j=4; j<16; j++){
                        expandedKey[(round*KEY_SIZE)+j] = expandedKey[((round)*KEY_SIZE)+(j-4)] ^ key[j];
                }
                round++;
        }

}

void getRoundKey(int round, char key[KEY_SIZE], char expandedKey[KEY_SIZE * (ROUND_COUNT + 1)]){
        for(int i=0; i<KEY_SIZE; i++){
                key[i] = expandedKey[(round*KEY_SIZE)+i];
        }
}

void AddRoundKey_128(int round, char key[KEY_SIZE], char expandedKey[KEY_SIZE * (ROUND_COUNT + 1)], char state[STATE_SIZE]){
	/*
	 * Get the Key
	 * */
	for(int i=0; i<KEY_SIZE; i++)
                key[i] = expandedKey[(round*KEY_SIZE)+i];
	/*
	 * Add the key
	 * */
        for(int i=0; i<STATE_SIZE && i < KEY_SIZE; i++)
                state[i] = state[i] ^ key[i];
}
