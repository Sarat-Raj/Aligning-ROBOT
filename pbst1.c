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
    int loop = 0;
    float angle_formed[25];
    FILE *fp = fopen("input - Sheet1(1).csv", "r");
    if(fp == NULL){printf("unable to open file");exit(1);}
    char buffer[1024];
    float sensor1Data[25], sensor2Data[25];
    int row = 0, column = 0, sD1 = 0, sD2 = 0;
    // a1 is the difference between two sensor data (opp side of the angle)
    // a2 is the distance betweeen the two sensors (adj side of the angle)
    float a1, a2 = 30.0;
    for(row = 0; fgets(buffer, sizeof(buffer), fp); sD1++, sD2++, row++)
    {
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
        printf(" row: %d \n",row);
    }
    fclose(fp);
    for(loop = 0; loop < row; loop++)
    {
        a1 = sensor1Data[loop]-sensor2Data[loop];
        angle_formed[loop] = (atan(a1/a2) * 180)/PI;
        printf("\n for Sensor1Data: %.2f , Sensor2Data: %.2f ,angle : %.2f",sensor1Data[loop],sensor2Data[loop],angle_formed[loop]);
        printf("\n");
    }
    for(loop=0; loop < row; loop++)
    {
        if (angle_formed[loop] < 0) angle_formed[loop]=180.0-angle_formed[loop];
        printf("corrected angle formed %f \n",angle_formed[loop]);
    }
}
 
