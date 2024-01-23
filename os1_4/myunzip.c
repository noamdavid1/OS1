#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <compressed_file.gpg>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd_gpg_gunzip[2];
    int pipefd_gunzip_tar[2];

    // Create pipes
    if (pipe(pipefd_gpg_gunzip) == -1 || pipe(pipefd_gunzip_tar) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork for gpg
    if (!fork()) {
        close(pipefd_gpg_gunzip[0]); // Close unused read end
        dup2(pipefd_gpg_gunzip[1], STDOUT_FILENO); // Redirect stdout to pipe
        execlp("gpg", "gpg", "--output", "-", "--encrypt", "--recipient", "yael4231@gmail.com", NULL);
        perror("execlp gpg");
        exit(EXIT_FAILURE);
    }

    close(pipefd_gpg_gunzip[1]); // Close write end in the parent

    // Fork for gunzip
    if (!fork()) {
        close(pipefd_gunzip_tar[0]); // Close unused read end
        dup2(pipefd_gpg_gunzip[0], STDIN_FILENO); // Redirect stdin to gpg pipe
        dup2(pipefd_gunzip_tar[1], STDOUT_FILENO); // Redirect stdout to pipe
        execlp("gunzip", "gunzip", NULL);
        perror("execlp gunzip");
        exit(EXIT_FAILURE);
    }

    close(pipefd_gpg_gunzip[0]); // Close read end in the parent
    close(pipefd_gunzip_tar[1]); // Close write end in the parent

    // Fork for tar
    if (!fork()) {
        close(pipefd_gunzip_tar[0]); // Close unused read end
        dup2(pipefd_gunzip_tar[1], STDOUT_FILENO); // Redirect stdout to pipe
        execlp("tar", "tar", "xf", "-", NULL);
        perror("execlp tar");
        exit(EXIT_FAILURE);
    }

    close(pipefd_gunzip_tar[1]); // Close write end in the parent

    // Wait for all child processes to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Decompression and decryption completed. Terminating.\n");

    return 0;
}
