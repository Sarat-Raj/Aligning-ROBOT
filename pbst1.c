#include<stdio.h>
#include<conio.h>
#include <string.h>
#include <math.h>
float PI = 3.14159;
void main()
{
// r = reads, pointer at the start
// a = reads, pointer at the end
// r+ = r + new data is written at the start (Both reading and writing)
// a+ = a + new data is written at the end (Both reading and writing)
// fscanf = 
// fgets = 
   int i = 0;
   int loop;
   float angle_formed;
   FILE *fp;
   fp = fopen("input - Sheet1(1).csv", "r");
   if(fp != NULL)
   {
       char buffer[1024];
       float sensor1Data[25], sensor2Data[25];
       int row = 0, column = 0, sD1 = 0, sD2 = 0;
       // a1 is the difference between two sensor data (opp side of the angle)
       // a2 is the distance betweeen the two sensors (adj side of the angle)
       int a1, a2 = 30;
       while(fgets(buffer, 1024, fp))
       {
           column = 0;
           row = 0;
           char* value = strtok(buffer, ", ");
           while (value)
           {
               // Column 1
               if (column == 0) 
               {
                   //s1 = sensor 1
                   printf("S1 : %s", value);
                   //I wanted to convert that value into a float
                   sensor1Data[sD1] = strtod(value, value);
               }
               // Column 2
               if (column == 1)
               {
                   //s2 = sensor 2
                   printf("\tS2 :%s", value);
                   //I wanted to convert that value into a float
                   sensor2Data[sD2] = strtod(value, value);
               }
               value = strtok(NULL, ", ");
               column++;
           }
           sD1++;
           sD2++;
           row++;
           printf("\n");
        }
    fclose(fp);
    for(loop = 0; loop < 10; loop++)  printf("\n %f, %f ", sensor1Data[loop],sensor2Data[loop]);
    for(i=0; sensor1Data[i]>0.0; i++)
    {
        angle_formed = (atan((float)sensor1Data[i]/(float)sensor2Data[i]) * 180)/PI;
        printf("\n for Sensor1Data: %f , Sensor2Data: %f ,angle : %f",sensor1Data[i],sensor2Data[i],angle_formed);
    }      
   }
   else printf("File is not Opened"); 
} 
