# OS1
In this assignment we were asked to perform 4 exercises.

## OS1_1


## OS1_2
In this exercise we were asked to work with a library.
We were asked to create a program that receives from the user 3 side lengths and checks if it is a Pythagorean triangle.
If it is a Pythagorean triangle, the program will print the angles in the triangle - in radians
If it is not a Pythagorean triple, the program will print Error on a separate line and exit.
We used the standard math library to use the functions asin(3).

![WhatsApp Image 2024-01-24 ](https://github.com/noamdavid1/OS1/assets/93923600/0ca9515f-91bb-4d71-a215-4ce662e94fc7)


## OS1_3
In the exercise we were asked to write a program that produces a polyalphabetic coder.
The program receives the 62-character long code that describes which letter each letter is mapped to. First 26 small letters, then 26 uppercase letters and then 10 digits (from 1 to 0) for the purpose of the example we used a Caesar cipher of +3
defghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abc
If the received key is invalid, the program will return null, otherwise the program will exit and return the structure of the encoder that will be transferred to the following functions:
+ *void * createCodec (char key[62]):* This function creates the encoder.
+ *int encode(char * textin, char * textout, int len, void * codec):* Encrypts textin into textout using the codec.
+ *int decode(char * textin, char * textout, int len, void * codec):* Decoding textin into textout using the codec.
In any case of success the function will return the number of decoded or encoded bits.
+ *Void freecodec(void * codec):* This function frees the memory taken by the codec parameter.

### You can see the two files in the image before running the code. So the source file contains text and the target file does not contain the encrypted text:
 ![WhatsApp Image 2024-01-24 at 13 57 46](https://github.com/noamdavid1/OS1/assets/93923600/450b1cea-132d-43fe-a0c4-258296aa2d96)
### After running it can be seen that the encrypted code has been written to the target file:
 ![WhatsApp Image 2024-01-24 at 13 57 46 (1)](https://github.com/noamdavid1/OS1/assets/93923600/42e89fed-f3ad-4bc9-ab60-a085b9353591)



## OS1_4

  

