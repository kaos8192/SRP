#include "SRP.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * Code by Geir Anderson
 * Calculates SRP percentages to determine if the system is either 1 or 2 state
 * and places into a central file after different states are tested
 * Fork based on exec.tgz
 */

void simulation(char a, char b, float reps)
{
    char fileto[] = "tempXXXXXX.txt";
    mkstemps(fileto, 4);

    FILE* theoutf = fopen(fileto, "w+");

    float rock = 0;
    float scissor = 0;
    float paper = 0;

    mc_init();

    for(int i = 0; i < reps; i++)
    {
        mc_play(a);
        mc_play(b);
        char c = mc_getPlay();
        
        if(c == 'r')
        {
            rock += 1;
        }
        else if(c == 's')
        {
            scissor += 1;
        }
        else
        {
            paper += 1;
        }
    }
    
    /*if(a == b)
    {
        fprintf(theoutf, "Demonstrates 1 or 2 state, both plays are the same.\n");
    }
    else
    {
        fprintf(theoutf, "Demonstrates more clearly is 1 or 2 state, since both plays are different.\n");
    }
    fprintf(theoutf, "%c , %c \n", a, b);*/
    fprintf(theoutf, "%c, %c:: s: %f r: %f p: %f\n", a, b, scissor/reps, rock/reps, paper/reps);

    fflush(theoutf);

    mc_print();
    mc_destroy();

    fclose(theoutf);
}

int main()
{
    int pid;
    for(int i = 1; i <= 9; i++)
    {

        pid = fork();
        if(pid <= 0)
        {
            char a[1];
            char b[1];

            if(i <= 3)
            {
                a[0] = 'r';
            }
            else if(i <= 6)
            {
                a[0] = 'p';
            }
            else
            {
                a[0] = 's';
            }

            if((i % 3) == 0)
            {
                b[0] = 'r';
            }
            else if((i % 3) == 1)
            {
                b[0] = 'p';
            }
            else if((i % 3) == 2)
            {
                b[0] = 's';
            }

            //char* sendin[] = {a, b, 0};
            /*if(execv("./sim", sendin) < 0)
            {
                printf("error");
            }*/

            simulation(a[0], b[0], 10000000);

            return 0;

            //printf("%c, %c, pid is %d\n", a[0], b[0], getpid());
            //return 0;
        }
    }
    if(pid > 0)
    {
        while(wait(NULL) >= 0){}
    }

    /*
    FILE* gp = fopen("gather.txt", "a+");

    fclose(gp);
    */

    //used in testing prior to gather above
    system("cat *.txt > gather.txt");

    //printf("parent is %d\n", getpid());
    return 0;
}
