# OS1
In this assignment we were asked to perform 4 exercises.

## OS1_1
In this exercise we were required to work with debug.
For the ID card that ends with check digits 1-3, we worked on bug "A" - a program that crashes due to division by zero.
And in case the identity card ends with check digit 4-6, we worked on a "B" bug - a program that crashes due to illegal memory access.

### We were asked to show a compilation of the program with and without debug
![WhatsApp Image 2024-01-24](https://github.com/noamdavid1/OS1/assets/93923600/9d4af998-3edf-4ce5-9771-c39a46036511)

We ran the program knowing that it would create a core file with and without debug. We were asked to open the core using gdb
### Running the program without debug
![WhatsApp Image 2024-01-24 at 13 55 47 (1)](https://github.com/noamdavid1/OS1/assets/93923600/ffec7081-ae8e-45c9-baf1-d3fd79e5ff0a)
### Running the program with debug
![WhatsApp Image 2024-01-24 at 13 55 47 (2)](https://github.com/noamdavid1/OS1/assets/93923600/ec3b3b4b-d793-44ed-8efe-d0a0632b2130)
![WhatsApp Image 2024-01-24 at 13 55 47 (3)](https://github.com/noamdavid1/OS1/assets/93923600/ef3262c9-5469-4932-bdd5-45f13cd4671a)

It can be seen that the difference in output between input with and without debugging is the exact location of the error.
So in the program with debug we found the relevant line of the fall in the code with the help of core. And in the program without the debug the exact location is not found.

### Finally, we demonstrated opening the core using a graphical debugger - DDD
![WhatsApp Image 2024-01-24 at 13 55 47 (5)](https://github.com/noamdavid1/OS1/assets/93923600/e65d043c-e922-4c2d-9c57-b36a3aff6ee8)
![WhatsApp Image 2024-01-24 at 13 55 47 (4)](https://github.com/noamdavid1/OS1/assets/93923600/26c965b3-c740-44df-b194-fba9d5c24b3b)

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
In this exercise we were required to work with processes.
We were asked to build a compressor-encryptor like zip with the help of several processes - merge a directory and sub-directories into one big file. Similarly, he knows how to open a large file and merge it into several files
We are interested in receiving two orders: myzip, myunzip
Both commands accept a parameter with the help of argv.

In the case of myzip it is a directory. The goal is to merge it into a large file (using tar), compress it (for example using compress) and encrypt it using gpg.
In the case of unzip it is a compressed file. We would like to decode it and deploy it.

### Collaborators
- *Noam David*
- *Yael Gabay*
