/*Fie P un proces ce determină cmmdc a două numere. Folosind o structură adecvată de astfel
de procese să se scrie un program ce determină cmmdc a N numere date.
*/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int cmmdc(int a,int b){
        while(a!=b){
                if(a>b)
                        a=a-b;
                else
                        b=b-a;
        }
        return a;
}
int main(int argc,char *argv[])
{
	int v[100];
	int n;
  
	pid_t pid = -1;
	int status;
	int val;
	printf("n=");
	scanf("%d\n",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&v[i]);
	printf("User input=");
	 for(int i=0;i<n;i++)
		printf("%d ",v[i]);
	printf("\n");
	int i = 0;
	while(i < n){ //facem n procese 
			pid = fork();
			if(pid == 0) //daca suntem in copil, incrementam pe i si continuam loop
			{
				i++;
			}
			else // daca suntem in parinte nu mai cream procese.
			{
				break;
			}
	}
	if(i != n){ // daca nu suntem in procesul "frunza", adica ultimul creat din ierarhie, atunci asteptam ca sa se termine copilul nostru
	// ierarhia se creeaza in urmatorul fel: primul, proces face un copil, si fiecare copil are
	//cate un singur copil, mai putin ultimul proces(i==n)
		waitpid(pid,&status,0);
		int exit_status = WEXITSTATUS(status); // statusul de terminare al procesului copil este cmmdc-ul numerelor primite de el
		val = cmmdc(v[i],exit_status);
		if(i == 0)
			printf("cmmdc = %d\n",val);
		exit(val);
	}
	else
	{// fiecare proces primeste cate un numar si eventual statusul de la copil, daca exista
	//ultimul proces nu primeste niciun numar si returneaza ultima valoare din vector
		exit(v[i-1]);
	}
	return 0;
}