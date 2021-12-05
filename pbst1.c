#include<stdio.h>
#include<conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
float PI = 3.14159;
void main()
{
// r = reads, pointer at the start
// a = reads, pointer at the end
// r+ = r + new data is written at the start (Both reading and writing)
// a+ = a + new data is written at the end (Both reading and writing)
// fscanf = 
// fgets = 
    int i = 0,loop = 0;
    float angle_formed;
    FILE *fp = fopen("input - Sheet1(1).csv", "r");
    if(fp == NULL){printf("unable to open file");exit(1);}
    char buffer[1024];
    float sensor1Data[25], sensor2Data[25];
    int row = 0, column = 0, sD1 = 0, sD2 = 0;
    // a1 is the difference between two sensor data (opp side of the angle)
    // a2 is the distance betweeen the two sensors (adj side of the angle)
    int a1, a2 = 30;
    for(row = 0; fgets(buffer, sizeof(buffer), fp); sD1++, sD2++, row++)
    {
        row = 0;
        char *value = strtok(buffer, ", ");
        for (column = 0; value; column++)
        {
            if (column == 0) 
            {
                //s1 = sensor 1
                printf("S1 : %s", value);
                //I wanted to convert that value into a float
                sensor1Data[sD1] = (float)strtod(value, NULL);
            }
            if (column == 1)
            {
                //s2 = sensor 2
                printf("\tS2 :%s", value);
                //I wanted to convert that value into a float
                sensor2Data[sD2] = (float)strtod(value, NULL);
            }
            value = strtok(NULL, ", ");
        }
        printf("\n");
    }
    fclose(fp);
    for(loop = 0; loop < 10; loop++)  printf("\n %.2f, %.2f ", sensor1Data[loop],sensor2Data[loop]);
    for(i = 0; sensor1Data[i] > 0.0; i++)
    {
        a1 = sensor1Data[i]-sensor2Data[i];
        angle_formed = (atan(a1/a2) * 180)/PI;
        printf("\n for Sensor1Data: %.2f , Sensor2Data: %.2f ,angle : %.2f",sensor1Data[i],sensor2Data[i],angle_formed);
    }      
}
 
