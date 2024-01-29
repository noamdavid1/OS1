#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd_tar_gzip[2];
    int pipefd_gzip_gpg[2];

    // Create pipes
    if (pipe(pipefd_tar_gzip) == -1 || pipe(pipefd_gzip_gpg) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork for tar
    if (!fork()) {
        close(pipefd_tar_gzip[0]); // Close unused read end
        dup2(pipefd_tar_gzip[1], STDOUT_FILENO); // Redirect stdout to pipe 
        execlp("tar", "tar", "cf", "-", argv[1], NULL);
        perror("execlp tar");
        exit(EXIT_FAILURE);
    }

    close(pipefd_tar_gzip[1]); // Close write end in the parent

    // Fork for gzip
    if (!fork()) {
        close(pipefd_gzip_gpg[0]); // Close unused read end
        dup2(pipefd_tar_gzip[0], STDIN_FILENO); // Redirect stdin to tar pipe
        close(pipefd_tar_gzip[1]); // Close unused write end
        dup2(pipefd_gzip_gpg[1], STDOUT_FILENO); // Redirect stdout to pipe
        execlp("gzip", "gzip", NULL);
        perror("execlp gzip");
        exit(EXIT_FAILURE);
    }

    close(pipefd_tar_gzip[0]); // Close read end in the parent
    close(pipefd_gzip_gpg[1]); // Close write end in the parent

    // Fork for gpg
    if (!fork()) {
        close(pipefd_gzip_gpg[1]); // Close unused write end
        close(pipefd_tar_gzip[0]); // Close unused read end

        dup2(pipefd_gzip_gpg[0], STDIN_FILENO); // Redirect stdin to gzip pipe
        execlp("gpg", "gpg", "-e", "--yes", "--recipient", "yael4231@gmail.com", NULL);
        perror("execlp gpg");
        exit(EXIT_FAILURE);
    }

    close(pipefd_gzip_gpg[0]); // Close read end in the parent
    close(pipefd_tar_gzip[1]); // Close unused write end

    // Wait for all child processes to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    //printf("Compression completed. Terminating.\n");

    return 0;
}
