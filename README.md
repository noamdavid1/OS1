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

## myzip
We will explain a little about the code:                                                                             
Initially you get the name of the folder to compress.
Then create two pipes for communication between processes - pipefd_tar_gzip - for communication between tar and gzip.
pipefd_gzip_gpg - for communication between gzip and gpg.
## Then there are three stages of fork:
+ *First step (tar):* Creates a child process for tar, which executes tar cf - <directory>. The tar output is directed to the pipefd_tar_gzip pipe.
dup2(pipefd_tar_gzip[1], STDOUT_FILENO): Returns tar's stdout to the created pipe, so that tar's output is piped.
execlp("tar", "tar", "cf", "-", argv[1], NULL): concatenates the tar command with the arguments "cf" (create file) and "-" (create output supported in stdout ), followed by the path to the folder you want to compress.
+ *Second step (gzip):* creates a child process for gzip, which receives the output from the pipefd_tar_gzip pipe and comes out compressed.
dup2(pipefd_gzip_gpg[1], STDOUT_FILENO): Returns gzip's stdout to the gpg communication pipe.
execlp("gzip", "gzip", NULL): call to gzip command.
+ *Third step (gpg):* Creates a child process for gpg, which receives the output from the pipefd_gzip_gpg pipe and encryption is performed.
dup2(pipefd_gzip_gpg[0], STDIN_FILENO): returns the stdin of gpg to the gzip communication pipe.
execlp("gpg", "gpg", "-e", "--yes", "--recipient", "yael4231@gmail.com", NULL): call to the gpg command with the appropriate arguments for encryption. --yes confirms all encryption-related questions automatically, and --recipient specifies the recipient of the public number or its email address.

Finally, the program closes the ends of the pipes that are not required in each process, and then waits for the end of each child process using wait.

![WhatsApp Image 2024-01-29 at 21 08 08 (1)](https://github.com/noamdavid1/OS1/assets/93923600/9efcec2e-e75b-4b13-91f4-f3d4b90d3708)

## myunzip
We will explain a little about the code:
In this code, a file is decoded and exploded and returned from an encrypted file to the original.
The program uses three child processes to perform the various steps of the operation. The decompressed file is transferred via pipes between the processes.
## Then there are three stages of fork:
+ *First step (gpg):* Decoding by GPG. The file is executed by GPG and the program uses the execlp function to replace the current process with a call to GPG and run it so that the input is passed to the next process program directly. At the end of the process, the content will be transferred to the next process using a pipe.
+ *Second step (gunzip):* Blast by gunzip. This process uses the execlp function to replace the current process and run gunzip. The input of this process is the exploded input it received from the previous operation. The result of the explosion is piped to the next process.
+ *Third step (tar):* Unloading the contents from the file by tar. This process uses the execlp function to replace the current process and run tar. The input of this process is the output of the previous pipe process, and its action is to disassemble the file and return the content to the original file.

Finally, the program closes the ends of the pipes that are not required in each process, and then waits for the end of each child process using wait.

![WhatsApp Image 2024-01-29 at 21 08 08 (2)](https://github.com/noamdavid1/OS1/assets/93923600/4c1d6e38-54d9-44fe-8040-b244c87328fc)

![WhatsApp Image 2024-01-29 at 21 08 08](https://github.com/noamdavid1/OS1/assets/93923600/160246fe-22a6-4351-8d15-38f5de112ce7)


### Collaborators
- *Noam David*
- *Yael Gabay*
