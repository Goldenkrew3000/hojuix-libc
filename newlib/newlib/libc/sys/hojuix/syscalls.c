#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

/*
 * Following the Linux x86_64 (SysV) calling convention (https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md)
 * %rax - Syscall number
 * %rdi - Arg0
 * %rsi - Arg1
 * %rdx - Arg2
 * %r10 - Arg3
 * %r8 - Arg4
 * %r9 - Arg5
*/

#define SYS_EXIT 7
#define SYS_IOCTL 10
#define SYS_GETPID 9

#define SYS_OPEN 3
#define SYS_CLOSE 4
#define SYS_WRITE 1
#define SYS_READ 2

#define SYS_FSTAT 18 // bullshit number for testing

void _exit(int status) {
	asm(
        "mov %0, %%rax\n\t"		// Syscall
        "mov %1, %%rdi\n\t"		// Status
        "int $0x80\n\t"
        :: "r"((uint64_t)SYS_EXIT), "r"((uint64_t)status)
        : "rax", "rbx", "memory"
    );
}

int getpid() {
	//
}

int fork() {
	//
}

int fstat(int file, struct stat *st) {
	// TODO implement
	asm(
        "mov %0, %%rax\n\t"
        "int $0x80\n\t"
        :: "r"((uint64_t)SYS_FSTAT)
        : "rax", "memory"
    );
}

int open(const char *name, int flags, ...) {
	//
}

int close(int file) {
	//
}

int write(int file, char *ptr, int len) {
	// TODO implement
	asm(
        "mov %0, %%rax\n\t"		// Syscall
		"mov %1, %%rdi\n\t"		// File descriptor
		"mov %2, %%rsi\n\t"		// Buffer
		"mov %3, %%rdx\n\t"		// Count
        "int $0x80\n\t"
        :: "r"((uint64_t)SYS_WRITE), "r"((uint64_t)file), "r"((uint64_t)ptr), "r"((uint64_t)len)
        : "rax", "rdi", "rsi", "rdx", "memory"
    );
}

int read(int file, char *ptr, int len) {
	//
}

int isatty(int file) {
	return 0; // TODO implement with SYS_IOCTL
}

// Bullshit pointer that will be easy to identify in %CR2 when its a dependency
char **environ = (char **)0x1234; /* pointer to array of char * strings that define the current environment variables */

int execve(char *name, char **argv, char **env);

int kill(int pid, int sig);
int link(char *old, char *new);
int lseek(int file, int ptr, int dir) {}
caddr_t sbrk(int incr) {}
int stat(const char *file, struct stat *st);
clock_t times(struct tms *buf);
int unlink(char *name);
int wait(int *status);
//int gettimeofday(struct timeval *p, struct timezone *z);

