#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <sched.h>
#include <linux/sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
	pid_t pid = getpid();
	int loop = 0;
	struct sched_param sss;
	sss.sched_priority = 0;
	int result = sched_setscheduler(0, 6, &sss);
	if (result < 0) {
		perror(NULL);
		exit(1);
	}
	while (loop < 500) {
		if (loop > 49 && loop % 50 == 0) {
			printf("Woohoo schedgy-poo: %d\n", result);
		}
		loop++;
	}
	return 0;
}
