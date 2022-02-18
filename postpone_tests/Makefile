all: resume_proc.x stop_proc.x ticker.x postpone_proc.x postpone_test.x


resume_proc.x: resume_proc.c
	cc resume_proc.c -o $@

stop_proc.x: stop_proc.c
	cc stop_proc.c -o $@

ticker.x: ticker.c
	cc ticker.c -o $@

postpone_proc.x: postpone_proc.c
	cc postpone_proc.c -o $@

postpone_test.x: postpone_test.c
	cc postpone_test.c -o $@

clean:
	rm *.x
