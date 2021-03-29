#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
	int ret;
	time_t t;
	struct sched_param sched;
	unsigned char mask;
	struct timespec tp;

	sched.sched_priority = 90;
	sched_setscheduler(getpid(), SCHED_FIFO, &sched);

	ret = sched_getscheduler(getpid());
	switch (ret) {
	case SCHED_OTHER:
		printf("pid:%d policy: SCHED_OTHER\n", getpid());
		break;

	case SCHED_FIFO:
		printf("pid:%d policy: SCHED_FIFO\n", getpid());
		break;

	case SCHED_RR:
		printf("pid:%d policy: SCHED_RR\n", getpid());
		break;

/*	case SCHED_BATCH:
		printf("pid:%d policy: SCHED_BATCH\n", getpid());
		break;

	case SCHED_IDLE:
		printf("pid:%d policy: SCHED_IDLE\n", getpid());
		break;

	case SCHED_DEADLINE:
		printf("pid:%d policy: SCHED_DEADLINE\n", getpid());
		break;
*/
	default:
		printf("pid:%d error policy\n", getpid());
		return -1;
	}

	printf("SCHED_FIFO max priority: %d\n",
		sched_get_priority_max(SCHED_FIFO));
	printf("SCHED_FIFO min priority: %d\n",
		sched_get_priority_min(SCHED_FIFO));

	sched_getparam(getpid(), &sched);
	printf("pid:%d priority:%d\n", getpid(),
		sched.sched_priority);
	sched.sched_priority = 80;
	sched_setparam(getpid(), &sched);
	sched_getparam(getpid(), &sched);
	printf("pid:%d priority:%d\n", getpid(),
		sched.sched_priority);

	printf("pid:%d priority:%d\n", getpid(),
		getpriority(PRIO_PROCESS, getpid()));
	setpriority(PRIO_PROCESS, getpid(), 10);
	printf("pid:%d priority:%d\n", getpid(),
		getpriority(PRIO_PROCESS, getpid()));

	printf("pid:%d priority by nice:%d\n", getpid(), nice(-5));

	sched_setscheduler(getpid(), SCHED_RR, &sched);
	sched_rr_get_interval(getpid(), &tp);
	printf("pid:%d interval: sec %d, nsec %d\n",
		getpid(), tp.tv_sec, tp.tv_nsec);

	sched_getaffinity(getpid(), sizeof(char), &mask);
	printf("pid:%d mask: 0x%x\n", getpid(), mask);

	mask = 0xff;
	sched_setaffinity(getpid(), sizeof(char), &mask);

	sched_getaffinity(getpid(), sizeof(char), &mask);
	printf("pid:%d mask: 0x%x\n", getpid(), mask);

	time(&t);
	printf("sched_yield before: %s", ctime(&t));
	sched_yield();
	time(&t);
	printf("sched_yield after: %s", ctime(&t));

	return 0;
}
