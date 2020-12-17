/*Se dă expresia aritmetică (a+b*c) / (a-b+d-c) + a*b*c*d. Să se scrie un program care determină
valoarea acestei expresii, astfel încât fiecare operație aritmetică să fie executată de câte
un proces.
*/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int add(int x, int y)
{
        return x + y;
}
int sub(int x, int y)
{
        return x - y;
}
int mul(int x, int y)
{
        return x * y;
}
int division(int x, int y)
{
        return x / y;
}
int main()
{
	int a, b, c, d, val = 0;
	pid_t pid1 = -1;
	pid_t pid2 = -1;
	pid_t pid3 = -1;
	pid_t pid4 = -1;
	pid_t pid5 = -1;
	pid_t pid6 = -1;
	pid_t pid7 = -1;
	pid_t pid8 = -1;
	pid_t pid9 = -1;
	int status;
	printf("a=");
	scanf("%d", &a);
	printf("b=");
	scanf("%d", &b);
	printf("c=");
	scanf("%d", &c);
	printf("d=");
	scanf("%d", &d);
	if (a - b + d - c == 0)
			printf("Division by zero!\n");

	pid1 = fork();
	if (pid1 == 0)
	{
			pid2 = fork();
			if (pid2 == 0)
			{
					pid3 = fork();
					if (pid3 == 0)
					{
							val = mul(b, c);
							printf("inside pid3: b*c=%d\n",val);
							exit(val);
					}
					else
					{
							waitpid(pid3, &status, 0);
							int val_ret3 = WEXITSTATUS(status);

							val = add(a, val_ret3);
							printf("inside pid2: a+b*c=%d\n",val);
							exit(val);
					}
			}
			else{
					pid4 = fork();
					if (pid4 == 0)
					{
							pid5 = fork();
							if (pid5 == 0)
							{
									val = sub(a, b);
									printf("inside pid5: a-b=%d\n",val);
									exit(val);
							}
							pid6 = fork();
							if (pid6 == 0)
							{
									val = sub(d, c);
									printf("inside pid6: d-c=%d\n",val);
									exit(val);
							}
							else{
									waitpid(pid5, &status, 0);
									int val_ret5 = WEXITSTATUS(status);
									waitpid(pid6, &status, 0);
									int val_ret6 = WEXITSTATUS(status);
									val = add(val_ret5, val_ret6);
									printf("inside pid4: a-b+d-c=%d\n",val);
									exit(val);
							}
					}
					else{
							waitpid(pid2, &status, 0);
							int val_ret2 = WEXITSTATUS(status);
							waitpid(pid4, &status, 0);
							int val_ret4 = WEXITSTATUS(status);
							val = division(val_ret2, val_ret4);

							printf("received (a+b*c) = %d\n",val_ret2);
							printf("received (a-b+d-c) = %d\n",val_ret4);

							printf("inside pid1: (a+b*c) / (a-b+d-c)=%d\n",val);
							exit(val);
					}
			}
	}
	else{
			pid7 = fork();
			if (pid7 == 0)
			{
					pid8 = fork();
					if (pid8 == 0)
					{
							val = mul(a, b);
							printf("inside pid8: a*b=%d\n",val);
							exit(val);
					}
					else{
							pid9 = fork();
							if (pid9 == 0)
							{
									val = mul(c, d);
									printf("inside pid9: c*d=%d\n",val);
									exit(val);
							}
							else{
									waitpid(pid8, &status, 0);
									int val_ret8 = WEXITSTATUS(status);
									waitpid(pid9, &status, 0);

									int val_ret9 = WEXITSTATUS(status);
									val = mul(val_ret8, val_ret9);
									printf("inside pid7: a*b*c*d=%d\n",val);
									exit(val);
							}
					}
			}
			else{
					waitpid(pid1, &status, 0);
					int val_ret1 = WEXITSTATUS(status);
					waitpid(pid7, &status, 0);
					int val_ret7 = WEXITSTATUS(status);
					val = add(val_ret1, val_ret7);

					printf("pid1: %d\n",val_ret1);
					printf("pid7: %d\n",val_ret7);

					printf("(a+b*c) / (a-b+d-c) + a*b*c*d=%d\n\n",val);
					printf("%d\n", val);
					return 0;
			}
	}
}
