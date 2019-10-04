#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ITERATIONS 5

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf( "usage: %s <PID>\n", argv[0] );
        return(-1);
    }

    long double a[4], b[4];
    long double pidTime = 0.0, aa = 0.0, bb = 0.0;
    long int clk;
    int i;
    FILE *fp;
    char stat[1024];

    clk = sysconf(_SC_CLK_TCK);

    if (clk == -1) {
        printf("Could not determine clock ticks per second");
        return(-1);
    }

    char *pidPath = malloc(strlen("/proc/stat/")+strlen(argv[1])+1);
    if (pidPath == NULL) {
        printf("Could not allocate memory for str\n");
        return(-1);
    } else {
        strcpy(pidPath, "/proc/");
        strcat(pidPath, argv[1]);
        strcat(pidPath, "/stat");
    }

    //for(i = 0; i < ITERATIONS; i++)
    {
        fp = fopen(pidPath,"r");
        if (fp == NULL) {
            perror(pidPath);
            return(-1);
        } else {
            fgets(stat, sizeof(stat), fp);
            sscanf(stat,"%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %Lf %Lf %Lf %Lf %*d %*d %*d %*d %*u",&a[0],&a[1],&a[2],&a[3]);
            fclose(fp);
            sleep(3);
        }

        fp = fopen(pidPath,"r");
        if (fp == NULL) {
            perror(pidPath);
            return(-1);
        } else {
            fgets(stat, sizeof(stat), fp);
            sscanf(stat,"%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %Lf %Lf %Lf %Lf %*d %*d %*d %*d %*u",&b[0],&b[1],&b[2],&b[3]);
			fclose(fp);
        }

        pidTime += (((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3])));
		//printf("pidCPU=%Lf\n", pidTime);
		//printf("pidCPU_1=%Lf\n", (b[0]+b[1]+b[2]+b[3]) );
    }
	aa = (a[0]+a[1]+a[2]+a[3]);
	bb = (b[0]+b[1]+b[2]+b[3]);
	FILE *fptr = fopen(argv[2], "a");
	fprintf(fptr,"%LF\t	%Lf\n", aa, bb);

    //pidTime = (pidTime / (clk * ITERATIONS));
    //printf("pidCPU=%Lf\n", pidTime);
    //printf("%ld", clk);
    free(pidPath);
    return(0);
}
