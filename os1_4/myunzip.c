#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <compressed_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd_gpg_gzip[2];
    int pipefd_gzip_tar[2];

    // Create pipes
    if (pipe(pipefd_gpg_gzip) == -1 || pipe(pipefd_gzip_tar) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork for gpg
    if (!fork()) {
        close(pipefd_gpg_gzip[0]);
        dup2(pipefd_gpg_gzip[1], STDOUT_FILENO);
        execlp("gpg", "gpg", "--decrypt", "--yes", "--batch", "--recipient", "yael4231@gmail.com", argv[1], NULL);
        perror("execlp gpg");
        exit(EXIT_FAILURE);
    } 

    close(pipefd_gpg_gzip[1]);

    // Fork for gunzip
    if (!fork()) {
        close(pipefd_gzip_tar[0]);
        dup2(pipefd_gpg_gzip[0], STDIN_FILENO);
        close(pipefd_gpg_gzip[0]);
        dup2(pipefd_gzip_tar[1], STDOUT_FILENO);
        execlp("gunzip", "gunzip", NULL);
        perror("execlp gunzip");
        exit(EXIT_FAILURE);
    } 

    close(pipefd_gpg_gzip[0]);
    close(pipefd_gzip_tar[1]);

    // Fork for tar
    if (!fork()) {
        close(pipefd_gpg_gzip[0]);
        close(pipefd_gpg_gzip[1]);
        close(pipefd_gzip_tar[1]);  // Close unused write end

        dup2(pipefd_gzip_tar[0], STDIN_FILENO);  // Redirect stdin to read from the pipe
        close(pipefd_gzip_tar[0]);  // Close unused read end
        execlp("tar", "tar", "xf", "-", NULL);
        perror("execlp tar");
        exit(EXIT_FAILURE);
    }

    close(pipefd_gzip_tar[0]);  // Close read end in the parent

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
 printf("Decompression completed. Terminating.\n");

    return 0;
}
