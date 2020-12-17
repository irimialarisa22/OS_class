#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/*Sa se numere toate caracterele fiecarei linii dintr-un fisier.
Nu se vor face presupuneri referitoare la lungimea maxima a unei linii.
*/
#define MAX_NUM 1000
#define MAX_LINE_LEN 2048

void fatal(char *msg) {
        printf("%s\n", msg);
    exit (1);
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char filename[100];
    char line[MAX_LINE_LEN];
    char *p;
    int i;
    int array[MAX_NUM] = { 0 };
    int count = 0;

    printf("Enter the filename: ");
    if (scanf("%s", filename) != 1)
        fatal("Bad filename entry");
    if ((fp = fopen(filename,"r")) == NULL)
        fatal("Unable to open the file");

    while ((p = fgets(line, MAX_LINE_LEN, fp)) != NULL) {
        if (count >= MAX_NUM)
                fatal("Break the array");
        while(*p){
                if (!isspace(*p))
                        array[count]++;
                p++;
           }
        count++;
    }
    if (fp != stdin)
        fclose(fp);
    for (i = 0; i < count; i++){
        printf ("line[%3d] : %d\n", i, array[i]);
    }
    return 0;
}