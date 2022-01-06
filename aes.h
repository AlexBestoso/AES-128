/*
 * All arrays supplied to this function must
 * be null terminated
 */
void aes_128_encipher(char state[STATE_SIZE], char key[KEY_SIZE]){
        char expandedKey[KEY_SIZE * (ROUND_COUNT+1)];
        int round = 0;

        expandKey_128(key, expandedKey);

	AddRoundKey_128(round, key, expandedKey, state);
        round++;

        for(int i=0; i<ROUND_COUNT - 1; i++){
                SubBytes(state);
           
                ShiftRows(state);
                MixColumns(state);

		AddRoundKey_128(round, key, expandedKey, state);
                round++;
        }

        SubBytes(state);
        ShiftRows(state);

	AddRoundKey_128(round, key, expandedKey, state);
}

void aes_128_decipher(char state[STATE_SIZE], char key[KEY_SIZE]){
        char expandedKey[KEY_SIZE * (ROUND_COUNT+1)];
        int round = ROUND_COUNT;

        expandKey_128(key, expandedKey);

	AddRoundKey_128(round, key, expandedKey, state);

        inv_ShiftRows(state);
        inv_SubBytes(state);

        round--;
        for(int i=0; i<ROUND_COUNT-1; i++){
                AddRoundKey_128(round, key, expandedKey, state);
                inv_MixColumns(state);
                inv_ShiftRows(state);

                inv_SubBytes(state);
                round--;
        }

        AddRoundKey_128(round, key, expandedKey, state);
}

