#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <minix/postpone.h>

#define CHILD_POSTPONE_INTERVAL 1000
#define CHILDREN 33

void handler(int signo);
void extra_child_proc(void);
void child_proc(void);

sigset_t old_mask;

int main(int argc, char* argv[]){

	pid_t my_pid, extra_child;
	pid_t ch_pids[CHILDREN];
	int postpone_interval;
	char* pend;

	struct sigaction sa;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGUSR1, &sa, NULL);

	sigset_t ss;
	sigemptyset(&ss);
	sigaddset(&ss, SIGUSR1);
	sigprocmask(SIG_BLOCK, &ss, &old_mask);
	

	my_pid = getpid();

	for (int i=0; i<CHILDREN ; i++){
		ch_pids[i] = fork();
		if (ch_pids[i] < 0){
			fprintf(stderr, "fork failed ... exiting\n");
			exit(1);
		}
		if (ch_pids[i] == 0){
		       child_proc(); 
		       //never returns
		}
	}

	for (int i=0; i<CHILDREN ; i++){
		postpone_proc(ch_pids[i], CHILD_POSTPONE_INTERVAL);
		kill(ch_pids[i], SIGUSR1);						// we expect handler to be delayed since target proc is postponed
	}

	postpone_proc(my_pid, CHILD_POSTPONE_INTERVAL/4);	// waiting for some time
	
	extra_child = fork();
	if (extra_child<0){
		fprintf(stderr, "fork failed ... exiting\n");
		exit(1);
	}
	if (extra_child == 0){
			extra_child_proc();
			// never returns
	}

	postpone_proc(extra_child, CHILD_POSTPONE_INTERVAL);

	kill(extra_child, SIGUSR1);							// waking from sigsuspend, expected to be postponed

	for (int i=0; i<CHILDREN ; i++){
		kill(ch_pids[i], SIGKILL); 						// killing postponed child, the handler for SIGUSR1 shall never be executed
	}

	postpone_proc(my_pid, CHILD_POSTPONE_INTERVAL/4);	// waiting for all exiting to be done

	for (int i=0; i<CHILDREN ; i++){					// reaping killed children
		int r, status;
		if (waitpid(ch_pids[i], &status, WNOHANG)<0){
				printf("FAIL!\n");
				exit(1);
		}
	}

	printf("OK\n");

	while (1) pause();	// waiting to be killed by extra child
	return 1;
}

void handler(int signo){
	write(1,"WRONG!\n", 7);
}

void extra_child_proc(void){
	close(1);	// to neutralize write from handler
	sigsuspend(&old_mask);
	kill(getppid(), SIGINT);
	exit(0);
}

void child_proc(void){
	sigsuspend(&old_mask);
	printf("WRONG!\n");
	exit(1);
}
