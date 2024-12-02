#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void read_dir(DIR *dir, char *file)
{
    DIR *temp_dir;
    struct dirent *directory;
    struct stat file_state;
    char buff[1024];

    while ((directory = readdir(dir)) != NULL)
    {
        // Skip "." and ".."
        if (!strncmp(directory->d_name, ".", 1) || !strcmp(directory->d_name, ".."))
        {
            continue;
        }

        // Skip deleted files (inode == 0)
        if (directory->d_ino == 0)
        {
            continue;
        }

        // Construct full path
        if (snprintf(buff, sizeof(buff), "%s/%s", file, directory->d_name) >= sizeof(buff))
        {
            fprintf(stderr, "Path too long: %s/%s\n", file, directory->d_name);
            continue;
        }

        puts(buff);

        // Get file info
        if (lstat(buff, &file_state) < 0)
        {
            perror("stat");
            exit(1);
        }

        // Check if it is a directory
        if (S_ISDIR(file_state.st_mode))
        {
            temp_dir = opendir(buff);
            if (temp_dir == NULL)
            {
                perror("opendir");
                continue;
            }
            read_dir(temp_dir, buff);
            closedir(temp_dir); // Close the subdirectory
            printf("\n");
        }
    }
}

int main(int argc, char *argv[])
{
    DIR *dir;
    char file[1024];

    if (argc == 1)
    {
        strcpy(file, ".");
    }
    else
    {
        if (snprintf(file, sizeof(file), "%s", argv[1]) >= sizeof(file))
        {
            fprintf(stderr, "Input path too long: %s\n", argv[1]);
            return 1;
        }
    }

    if ((dir = opendir(file)) == NULL)
    {
        perror("opendir");
        exit(1);
    }

    read_dir(dir, file);
    closedir(dir); // Close the main directory
    return 0;
}
