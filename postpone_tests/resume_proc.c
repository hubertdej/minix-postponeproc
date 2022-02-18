#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <minix/postpone.h>

int main(int argc, char* argv[]){

	int pid_to_resume;
	char* pend;

	if (argc!=2) {
		fprintf(stderr,"Usage: %s PID_TO_RESUME\n", argv[0]);
		return 1;
	}

	errno=0;
	pid_to_resume = strtol(argv[1], &pend, 10);
	if ( (*pend != 0) || (errno!=0) ) {
		fprintf(stderr, "%s: invalid argument\n", argv[0]);
		return 1;
	}

	if (resume_proc(pid_to_resume) == -1){
		fprintf(stderr, "%s: resuming %d failed with errno: %s\n", argv[0], pid_to_resume, strerror(errno));
		return 1;
	};
	return 0;
}
