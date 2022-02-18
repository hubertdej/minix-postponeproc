#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int signo){
	write(1,"HANDLER\n", 8);
}

int main(){
	int i;
	
	struct sigaction sa;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGUSR1, &sa, NULL);

	i=0;
	while (1){
		printf("TICK: %d\n", i++);
		sleep(1);
	}
	return 1;
}
