extern int write(unsigned int fd, char * str, unsigned int size);
extern void pause(void);
extern int read(unsigned int fd, char * str, unsigned int size);
extern void halt(void);

int main() {
	//halt();
	pause();
	char str[] = "hi mothafuckas";
	write(1, str, 14);
	return 0xDEADBEEF;
}
