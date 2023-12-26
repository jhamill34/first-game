#include <unistd.h>
#include <stdio.h>

long myadd(long a, long b);
void reverse(char *buffer, size_t length);

size_t tostring(char *buffer, size_t length, long a) {
	int i = 0;
	while (a > 0 && i < (length - 2)) {
		buffer[i] = a % 10 + '0';
		a /= 10;
		i++;
	}
	buffer[i] = '\n';
	buffer[i + 1] = '\0';

	reverse(buffer, i);

	return i;
}

void start() {
	long a = 0xcafebabe;
	long b = 0xdeadbeef;
	myadd(a, b);

	syscall(1, 0);
}
