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
    int loop = 0,  row = 0, column = 0, sD1 = 0, sD2 = 0;
    float angle_formed[25], sensor1Data[25], sensor2Data[25];
    FILE *file_sensor_data = fopen("input - Sheet1(1).csv", "r");
    FILE *file_output_data;
    if(file_sensor_data == NULL){printf("unable to open file");exit(1);}
    char buffer[1024];
    // a1 is the difference between two sensor data (opp side of the angle)
    // a2 is the distance betweeen the two sensors (adj side of the angle)
    float a1, a2 = 30.0;
    for(row = 0; fgets(buffer, sizeof(buffer), file_sensor_data); sD1++, sD2++, row++)
    {
        char *value = strtok(buffer, ", ");
        for (column = 0; value; column++)
        {
            //sensor 1
            if (column == 0) 
            {
                printf("S1 : %s", value);
                //I wanted to convert that value into a float
                sensor1Data[sD1] = (float)strtod(value, NULL);
            }
            //sensor 2
            if (column == 1)
            {
                //I wanted to convert that value into a float
                sensor2Data[sD2] = (float)strtod(value, NULL);
            }
            value = strtok(NULL, ", ");
        }
    }
    fclose(file_sensor_data);
    for(loop = 0; loop < row; loop++)
    {
        a1 = sensor1Data[loop]-sensor2Data[loop];
        angle_formed[loop] = (atan(a1/a2) * 180)/PI;
    }
    file_output_data = fopen("output_data.csv", "a");
    if (!file_output_data) { printf("Error creating/ opening line"); exit(1); }    
    for(loop=0; loop < row; loop++)
    {
        if (angle_formed[loop] < 0) angle_formed[loop]=180.0-angle_formed[loop];
        //printf("corrected angle formed %f \n",angle_formed[loop]);
        fprintf(file_output_data,"%f,",angle_formed[loop]);
    }
}
 
