#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <minix/postpone.h>

int main(int argc, char* argv[]){

	int pid_to_postpone;
	int postpone_interval;
	char* pend;

	if (argc!=3) {
		fprintf(stderr,"Usage: %s PID_TO_RESUME POSTPONE_INTERVAL\n", argv[0]);
		return 1;
	}

	errno=0;
	pid_to_postpone = strtol(argv[1], &pend, 10);
	if ( (*pend != 0) || (errno!=0) ) {
		fprintf(stderr, "%s: invalid argument PID_TO_RESUME\n", argv[0]);
		return 1;
	}
	
	errno=0;
	postpone_interval = strtol(argv[2], &pend, 10);
	if ( (*pend != 0) || (errno!=0) ) {
		fprintf(stderr, "%s: invalid argument POSTPONE_INTERVAL\n", argv[0]);
		return 1;
	}

	if (postpone_proc(pid_to_postpone, postpone_interval) == -1){
		fprintf(stderr, "%s: postponing %d failed with errno: %s\n", argv[0], pid_to_postpone, strerror(errno));
		return 1;
	};
	return 0;
}
