/*Să se implementeze următorul sistem de procese, în care muchiile indică modul de comunicare între procese:
     1      1 - citeste de la intrarea standard linii de maxim 30 de caractere si scrie in prima iesire cifrele si in cea de-a doua iesire literele
	/ \     2 - afiseaza la iesirea standard
   2   3    3 - tranforma literele mici in litere mari si le afiseaza la iesirea standard
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char str[31];
	int fd1[2];  // parent to child 1 (1 - 2 from diagram)	
	int fd2[2];  // parent to child 2 (1 - 3 from diagram)
    pipe(fd2);
	pipe(fd1);
    int pid1 = fork();
	// Create the first process
    if (pid1 == 0) {
        char array[31];
		while(1)
		{
			read(fd1[0], &array, 30);
			printf("Numbers are: %s\n",array);
		}
        exit(0);
    }
    // Create the second process
    int pid2 = fork();
    if (pid2 == 0) {
        char array[31];
		while(1)
		{
			read(fd2[0], &array, 30);
			int i = 0;
			while (array[i] != '\0') {
				if ('a' <= array[i] && array[i] <= 'z') {
					array[i] -= 32;
				}
				i++;
			}
				printf("Capital letters are: %s\n", array);
		}
        exit(0);
    }
	
	printf("Enter an array:");
    if (pid1 != 0 && pid2 != 0) {
		char numbers[30], letters[30];
		while(1)
		{
			fgets(str,30,stdin);
			int i = 0;
			int rez1 = 0,rez2 = 0;
			while (str[i] != '\0') {
				if ('0' <= str[i] && str[i] <= '9') {
					numbers[rez1] = str[i];
					rez1++;
				} else {
					letters[rez2] = str[i];
					rez2++;
				}
            i++;
        }
        numbers[rez1] = '\0';
        letters[rez2] = '\0';
        write(fd1[1], &numbers, 30);
        write(fd2[1], &letters, 30);
		}
    } else {
        printf("The processes could not be created!");
    }
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[1]);
	close(fd2[0]);
    return 0;
}