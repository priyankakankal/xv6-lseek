#include "types.h"
#include "user.h"
#include "fcntl.h"

/* Funtion to generate random number from 1 - 10 */
int generate_rand(int seed) {
	static int i = 0, x0;
	int x1, a = 1, c = 1;

	if(!i)
		x0 = seed;
	i++;
	x1 = (a*x0 + c) % 10;
	x0 = x1;
	return x1;
}

int main(int argc, char *argv[]) {
	int fd1, fd2, tot_size, part_size, i, rand_num, time;
	char *buf;

	if(argc < 2) {
		printf(1, "Too less arguments\n");
		exit();
	}

	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1) {
		printf(1, "Error in opening file\n");
		exit();
	}

	// Deleting previously available copy file
	unlink("copy");

	fd2 = open("copy", O_CREATE | O_WRONLY);
	if(fd2 == -1) {
		printf(1, "Error in opening file\n");
		exit();
	}

	tot_size = lseek(fd1, 0, SEEK_END);
	part_size = tot_size / 10;

	buf = (char *)malloc((part_size + tot_size%10 + 1)*sizeof(char));

	time = uptime();

	for (i = 0; i < 10; i++) {
		rand_num = generate_rand(time);

		lseek(fd1, part_size*rand_num, SEEK_SET);
		lseek(fd2, part_size*rand_num, SEEK_SET);
		

		if(rand_num == 9) {
			/* If file size is not divisible by 10, consider (part_size + tot_size%10) for one of the parts*/
			read(fd1, buf, part_size + tot_size%10);
			write(fd2, buf, part_size + tot_size%10);

		} else {
			read(fd1, buf, part_size);
			write(fd2, buf, part_size);
		}
		
	}

	close(fd1);
	close(fd2);
	exit();
}