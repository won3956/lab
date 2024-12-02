#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void rm_command(const char *file) {
    if (unlink(file) == 0) {
        printf("File '%s' removed successfully.\n", file);
    } else {
        perror("Error removing file");
    }
}

void mv_command(const char *source, const char *destination) {
    if (rename(source, destination) == 0) {
        printf("File '%s' moved/renamed to '%s'.\n", source, destination);
    } else {
        perror("Error moving/renaming file");
    }
}

void cat_command(const char *file) {
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), f)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(f);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        fprintf(stderr, "Commands:\n");
        fprintf(stderr, "  rm <file>             Remove a file\n");
        fprintf(stderr, "  mv <source> <dest>    Move/rename a file\n");
        fprintf(stderr, "  cat <file>            Display file content\n");
        return 1;
    }

    if (strcmp(argv[1], "rm") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s rm <file>\n", argv[0]);
            return 1;
        }
        rm_command(argv[2]);
    } else if (strcmp(argv[1], "mv") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s mv <source> <dest>\n", argv[0]);
            return 1;
        }
        mv_command(argv[2], argv[3]);
    } else if (strcmp(argv[1], "cat") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s cat <file>\n", argv[0]);
            return 1;
        }
        cat_command(argv[2]);
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        fprintf(stderr, "Available commands: rm, mv, cat\n");
        return 1;
    }

    return 0;
}
