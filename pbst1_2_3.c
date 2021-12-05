#include<stdio.h>
#include<conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
float PI = 3.14159, angle_formed[25], sensor1Data[25], sensor2Data[25], a1[25], a2 = 30.0, current_distance_from_wall[25], cm_per_2k_rev = 15.708;
int loop = 0,  row = 0, column = 0, sD1 = 0, sD2 = 0, rev_per_rotation = 2000, rota_per_turn = 180, m1[25], m2[25], m3[25], m4[25], rev[25], bot_dir1[25], bot_dir2[25]; 
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
        a1[loop] = sensor1Data[loop]-sensor2Data[loop];
        angle_formed[loop] = (atan(a1[loop]/a2) * 180)/PI;
        printf("\nangle_formed[%d]:%f",loop+1,angle_formed[loop]);
    }
}

void pbst2()
{
    for (loop = 0; loop < row; loop++)
    {
        if (angle_formed[loop] > 0) bot_dir1[loop]=1;//clockwise
        if (angle_formed[loop] < 0) bot_dir1[loop]=0;//anticlockwise
        if (angle_formed[loop] == 0) {rev[loop] = 0; bot_dir1[loop] = 1;}
        rev[loop] = (int)abs((rev_per_rotation*angle_formed[loop])/rota_per_turn);
        //instead just doing this, a better approach would be as one rev of motor = 10pi cms, radius = 30 cms, cal angle based on that value
        // but opting this metod as its quicker
        m3[loop]=rev[loop];
        m4[loop]=rev[loop];
        printf("\n rev[%d] = %d : direction = %d",loop,m3[loop],bot_dir1[loop]);
    }

}

void pbst3()
{
    for (loop = 0; loop < row; loop++)
    {
        current_distance_from_wall[loop] = abs(a1[loop]);
        if (current_distance_from_wall[loop] > 30) 
        {
            m1[loop] = (int)((current_distance_from_wall[loop]-30)*2000)/cm_per_2k_rev; 
            m2[loop] = m1[loop]; 
            bot_dir2[loop]=1;
        }
        if (current_distance_from_wall[loop] < 30) 
        { 
            m1[loop] = (int)((30 - current_distance_from_wall[loop])*2000)/cm_per_2k_rev; 
            m2[loop] = m1[loop]; 
            bot_dir2[loop]=0;
        }
        if (current_distance_from_wall[loop] == 30) 
        {
            m1[loop] = 0; 
            m2[loop] = m1[loop]; 
            bot_dir2[loop]=1;
        }
        printf("\ncurrent_distance_from_wall[%d]:%f",loop,current_distance_from_wall[loop]);
        printf("\nm1:%d\t,m2:%d\t,botdir2[loop]:%d\t",m1[loop],m2[loop],bot_dir2[loop]);
    }
}

void wroutdataf()
{   
    file_output_data = fopen("output_data.csv", "w");
    if (!file_output_data) { printf("Error creating/ opening line"); exit(1); }    
    for (loop = 0; loop < row; loop++)
    {
        if (bot_dir1[loop] == 1 && bot_dir2[loop] == 1) fprintf(file_output_data,"%f,%d,%d,%d,%d,%s,%d,%d,%d,%d,%s\n",angle_formed[loop],0,0,m3[loop],m4[loop],"clockwise",m1[loop],m2[loop],0,0,"clockwise");
        if (bot_dir1[loop] == 1 && bot_dir2[loop] == 0) fprintf(file_output_data,"%f,%d,%d,%d,%d,%s,%d,%d,%d,%d,%s\n",angle_formed[loop],0,0,m3[loop],m4[loop],"clockwise",m1[loop],m2[loop],0,0,"anticlockwise");
        if (bot_dir1[loop] == 0 && bot_dir2[loop] == 1) fprintf(file_output_data,"%f,%d,%d,%d,%d,%s,%d,%d,%d,%d,%s\n",angle_formed[loop],0,0,m3[loop],m4[loop],"anticlockwise",m1[loop],m2[loop],0,0,"clockwise");
        if (bot_dir1[loop] == 0 && bot_dir2[loop] == 0) fprintf(file_output_data,"%f,%d,%d,%d,%d,%s,%d,%d,%d,%d,%s\n",angle_formed[loop],0,0,m3[loop],m4[loop],"anticlockwise",m1[loop],m2[loop],0,0,"anticlockwise");
    }
    fclose(file_output_data);
}

void main()
{
    create_sensorData_1_2();
    pbst1();
    pbst2();
    pbst3();
    wroutdataf();
}
 
