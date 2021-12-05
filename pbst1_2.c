#include<stdio.h>
#include<conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
float PI = 3.14159, angle_formed[25], sensor1Data[25], sensor2Data[25], a1, a2 = 30.0, rev[25];
int loop = 0,  row = 0, column = 0, sD1 = 0, sD2 = 0, rev_per_rotation = 2000, rota_per_turn = 180, m1 = 0, m2 = 0, m3, m4, bot_dir[25]; 
// a1 is the difference between two sensor data (opp side of the angle)
// a2 is the distance betweeen the two sensors (adj side of the angle)
// assuming that one revolution of the wheel, there is a 180° turning
FILE *file_sensor_data, *file_output_data;
    
void create_sensorData_1_2()
{
    file_sensor_data = fopen("input - Sheet1(1).csv", "r");
    if(file_sensor_data == NULL){printf("unable to open file");exit(1);}
    char buffer[1024];
    for(row = 0; fgets(buffer, sizeof(buffer), file_sensor_data); sD1++, sD2++, row++)
    {
        char *value = strtok(buffer, ", ");
        for (column = 0; value; column++)
        {
            //sensor 1
            if (column == 0) 
            {
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
}

void pbst1()
{
    for(loop = 0; loop < row; loop++)
    {
        a1 = sensor1Data[loop]-sensor2Data[loop];
        angle_formed[loop] = (atan(a1/a2) * 180)/PI;
        printf("\nangle_formed[%d]:%f",loop+1,angle_formed[loop]);
    }
}

void pbst2()
{
    for (loop = 0; loop < row; loop++)
    {
        if (angle_formed[loop] > 0) bot_dir[loop]=1;//clockwise
        if (angle_formed[loop] < 0) bot_dir[loop]=0;//anticlockwise
        if (angle_formed[loop] == 0) {rev[loop] = 0; bot_dir[loop]=0;}
        rev[loop] = abs((rev_per_rotation*angle_formed[loop])/rota_per_turn);
        //instead just doing this, a better approach would be as one rev of motor = 10pi cms, radius = 30 cms, cal angle based on that value
        // but opting this metod as its quicker
        printf("\n rev[%d] = %f : direction = %d",loop,rev[loop],bot_dir[loop]);
    }

}

void wroutdataf()
{   
    file_output_data = fopen("output_data.csv", "a");
    if (!file_output_data) { printf("Error creating/ opening line"); exit(1); }    
    for (loop = 0; loop < row; loop++)
    {
        if (bot_dir[loop] == 1) fprintf(file_output_data,"%f,%d,%d,%d,%d,%s\n",angle_formed[loop],m1,m2,m3=(int)rev[loop],m4=(int)rev[loop],"clockwise");
        if (bot_dir[loop] == 0) fprintf(file_output_data,"%f,%d,%d,%d,%d,%s\n",angle_formed[loop],m1,m2,m3=(int)rev[loop],m4=(int)rev[loop],"anticlockwise");
        
    }
    fclose(file_output_data);
}

void main()
{
    create_sensorData_1_2();
    pbst1();
    pbst2();
    wroutdataf();
}
 
