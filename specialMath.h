int countBinaryDigits(int value){
        int ret = 0;
        while(value > 0){
                value = value / 2;
                ret++;
        }
        return ret;
}

int buildBinaryNumber(int value, unsigned int *binaryNumber, int binarySize){
        // Shift Base value is 0x01
        int ret = 0;
        memset(binaryNumber, 0x00, binarySize);
        for(int i=0; i<binarySize; i++){ 
                binaryNumber[i] = (value & (0x01<<i));
                if((value & (0x01<<i)) != 0){
                        ret++;
                }
        }
        return ret;
}

int buildBinaryPolynomial(int value, unsigned int *polynomial, size_t size){
        int binaryDigits = countBinaryDigits(value);
        unsigned int binaryNumber[binaryDigits];
        int polySize = buildBinaryNumber(value, binaryNumber, binaryDigits);

        int j = 0;
        for(int i=0; i<binaryDigits && j < size; i++){
                if(binaryNumber[i] != 0){
                        if(j < polySize)
                                polynomial[j] = i;
                        j++;
                }
        }

        return polySize;
}

int mod(int value, int field){
	if((value + field) == 0)
                return 0;

        int valueIsNegative = (value < 0) ? 1 : 0;
        int greaterThanField = ((-1)*value > (-1)*field) ? 1 : 0;
        int fieldIsNegative = (field < 0)  ? 1 : 0;

        if(!valueIsNegative && !fieldIsNegative){
                return value % field;
        }else if(!valueIsNegative && fieldIsNegative){
                field = (-1)*field;
                return (value % field) * (-1);
        }else if(greaterThanField && !fieldIsNegative){
                return field - (((-1)*value) % field);
        }else if(!greaterThanField && !fieldIsNegative){
                return field - (-1)*value;
        }else if(greaterThanField && fieldIsNegative){
                field = (-1)*field;
                return (field - (((-1)*value) % field)) * (-1);
        }else{
                field = (-1)*field;
                return (field - (-1)*value) * (-1);
        }
}

int galoisMod(int value, int field){
        if(value <= 256 || value == 0)
                return value;

        if(value < 0)
                value = (value & 0xf0)+(value & 0x0f);

        int galoisField = field << (countBinaryDigits(value) - countBinaryDigits(field));
        while(value > 256){
                value = value ^ galoisField;
                if(value <= 256)
                        break;
                galoisField = field << (countBinaryDigits(value) - countBinaryDigits(field));
        }

        if(value < 0)
                value = (value & 0xf0)+(value & 0x0f);

        return value;
}

char galoisMultiply(const unsigned int x, char y){
	unsigned int ret = 0x00;
        const unsigned int shifter = 0x1;
        unsigned int _y = y;

        if(y < 0){
                _y = (y & 0xf0)+(y & 0x0f);
        }

        unsigned int polynomial[100];
        size_t polySize = buildBinaryPolynomial(x, polynomial, 100);

        /* where p = 0, and s is an array of polynomial subscripts
         * p = p[i] XOR (y LEFT_SHIFT s[i])
         * */
        for(int i=0; i<polySize && i<100; i++){
                ret = ret ^ (_y << polynomial[i]);
        }

        return ret;
}
