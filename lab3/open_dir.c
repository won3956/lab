#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *dirent;

	if(argc < 2)
	{
		fprintf(stderr, "use Method: %s <path name>\n", argv[0]);
		exit(1);
	}

	if((dir = opendir (argv[1])) < 0)
	{
		printf(" open failed.\n");
		exit(1);
	}

	if((dir = opendir(argv[1])) < 0)
	{
		printf("open failed.\n");
		exit(1);
	}

	// dirent d_name = file name d_ino = directory inode number
	while((dirent = readdir (dir)) != NULL)
	{
		printf("%s %ld\n", dirent->d_name, dirent->d_ino);
	}
	closedir(dir);

	return 0;
}
