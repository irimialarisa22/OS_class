/*Clientul ii transmite serverului un nume de director si primeste de la acesta lista tuturor fisierelor text din directorul respectiv, 
respectiv un mesaj de eroare daca directorul respectiv nu exista.
*/
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <pthread.h>
#include <wait.h>
#include <string.h>

int main() {
	int pipefp[2], pipepf[2];
	if(pipe(pipepf) == -1) {
		printf("The programme gives an error");
		return 1;
	}
	if(pipe(pipefp) == -1) {
		printf("The programme gives an error");
		return 1;
	}
	int count = 999; // count este numarul de cate ori va rula serverul.
	// Daca se doreste rulare la infinit, atunci se scrie mai jos while(1) si se scoate count-- de jos.
	while (count > 0) {
		int pid = fork();
		if (pid == -1) {
		printf("The fork could not be created!");
		return 1;
	}

	if (pid == 0) {
		//client, adica copilul
		char fisier[30];
		printf("Enter the directory: ");
		scanf("%s",fisier);
		int nr = write(pipefp[1], fisier, strlen(fisier));
		char raspuns[400];
		read(pipepf[0], raspuns, 400);
		printf("Child: The server returned: %s \n", raspuns);
		return 0;
	}
	else {
		//server, adica parintele
		char director[30] = "";
		int re = read(pipefp[0], director, 30);
		char comanda[40] = "./one.sh ";
		strcat(comanda, director);
		FILE* proc = popen(comanda,"r");
		char rez[400];
		fgets(rez, 400, proc);
		write(pipepf[1],rez,400);
	}
	count--;
	}
	close(pipefp[0]);
	close(pipepf[1]);
	close(pipefp[1]);
	close(pipepf[0]);
	return 0;
}