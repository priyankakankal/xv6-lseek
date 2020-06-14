#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {

	int fd, len, readcount = 0;
	char *string;
	char *buf;

	if(argc < 5) {
		printf(1, "Too less arguments\n");
		exit();
	}

	len = atoi(argv[3]);
	string = argv[4];
	buf = (char *)malloc((len + 1)*sizeof(char));

	fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		printf(1, "Error in opening file\n");
		exit();
	}

	if(lseek(fd, atoi(argv[2]), SEEK_CUR) == -1) {
		printf(1, "Error in lseek\n");
		exit();
	}

	readcount = read(fd, buf, len);
	if(readcount == -1) {
		printf(1, "Error in reading file\n");
		exit();
	}

	buf[readcount] = '\0';

	if(strcmp(string, buf) == 0) {
		printf(1, "Equal strings\n");
	} else {
		printf(1, "Not equal strings\n");
	}

	close(fd);
	exit();
}
