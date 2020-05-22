#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define CHILDNUM 5
#define BASE 30000000


int creat_sem(int num)
{
	int semid, ret;
	
	semid = semget(IPC_PRIVATE, num, 
		IPC_CREAT | 0600);
	if (semid == -1) {
		perror("semget");
		return -1;
	}

	return semid;
}

int init_semphore(int semid, int numth, int val)
{
	int ret;

	ret = semctl(semid, numth, SETVAL, val);
	if (ret == -1) {
		perror("semctl");
		return -1;
	}

	return 0;
}

int p(int semid, int numth)
{
	int ret;
	struct sembuf op;

	op.sem_num = numth;
	op.sem_op = -1;
	op.sem_flg = 0;

	while (1) {
		ret = semop(semid, &op, 1);
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			else {
				perror("semop");
				return -1;
			}	
		}
		if (ret == 0)
			break;
	}

	return 0;
}


void v(int semid, int numth)
{
	int ret;
	struct sembuf op;

	op.sem_num = numth;
	op.sem_op = 1;
	op.sem_flg = 0;

	semop(semid, &op, 1);

	return;
}

void do_prime(long long prime)
{
	long long i, flag = 0;

	for (i = 2; i < prime; i++) {
		if (prime % i == 0) {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		printf("val=%lld is a prime!\n", prime);
	} else {
		printf("val=%lld is not a prime!\n", 
			prime);
	}
}

int main(void)
{
	int i, ret, semid;
	
	semid = creat_sem(1);
	if (semid == -1) {
		exit(1);
	}
	ret = init_semphore(semid, 0, CHILDNUM);
	if (ret == -1) {
		exit(1);
	}

	for (i = 0; i < 200; i++) {
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");
			return -1;
		}

		if (pid == 0) {
			long long val = i + BASE;
	//		p(semid, 0);
			do_prime(val);
	//		v(semid, 0);
			exit(0);
		}

	}

	return 0;
}
