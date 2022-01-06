# AES-128-RAW

What is AES RAW? Basically it's the Rijndael cipher with a 128 bit key.

With the last update of this code, I simplifed the math functions and fixed up the array sizes. 
There was no need to have the extra bytes for null termination.

This code will soon be implemented as a c++ class.

To compile the file, you need to link the math library, here is what was used in the development of the headers:
gcc main.c -lm -o AES_128_RAW
