/*Să se implementeze următorul sistem de procese, în care muchiile indică modul de comunicare între procese:
     1      1 - citeste de la intrarea standard linii de maxim 30 de caractere si scrie in prima iesire cifrele si in cea de-a doua iesire literele
	/ \     2 - afiseaza la iesirea standard
   2   3    3 - tranforma literele mici in litere mari si le afiseaza la iesirea standard
*/
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char str[31];
	mkfifo("fifop",0666);
	mkfifo("fifof",0666);
	int fdp = open("fifop",O_RDWR);
	int fdf = open("fifof",O_RDWR);
    int pid1 = fork();
	// Create the first process
    if (pid1 == 0) {
        char array[31];
		while(1)
		{
			read(fdp, &array, 30);
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
			read(fdf, &array, 30);
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
        write(fdp, &numbers, 30);
        write(fdf, &letters, 30);
		}
    } else {
        printf("The processes could not be created!");
    }
	close(fdp);
	close(fdf);
    return 0;
}