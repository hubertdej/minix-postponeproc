#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <minix/postpone.h>

int main(int argc, char* argv[]){

	int pid_to_stop;
	char* pend;

	errno=0;
	pid_to_stop = strtol(argv[1], &pend, 10);
	if ( (*pend != 0) || (errno!=0) ) {
		fprintf(stderr, "%s: invalid argument\n", argv[0]);
		return 1;
	}

	if (stop_proc(pid_to_stop) == -1){
		fprintf(stderr, "%s: stopping %d failed with errno: %s\n", argv[0], pid_to_stop, strerror(errno));
		return 1;
	};
	return 0;
}
