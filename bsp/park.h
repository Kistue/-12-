#include "main.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

#ifndef _PARK_H_
#define _PARK_H_


//车辆结构体
typedef struct Car 
{
    char type[5];
    char id[5];
}Car;

//时间结构体
typedef struct Time
{
    int year;
    int month;
    int date;
    int hour;
    int minute;
    int second;
}Time;

typedef struct Parking
{
    Car car;
    Time time;
    int ifpark;
    int location;
}Parking;

extern  UART_HandleTypeDef huart1;
extern Parking parking[8];
extern Car car;
extern Time time;




void Init_parking(Parking* parking);
Time Init_Time(Time time);
Car Init_Car(Car car);
char* substring(char* Rx_data , int begin , int lenth);
int Analysic(char* Rx_data);
int Park(Parking* parking , Car car , Time time);
char* splitString(const char* input, int start, int length);
int Analysic(char *Rx_data);
int go_out(Car car , Time time , Parking* parking);
void ifpark_Init(Parking* parking);
int ifpark(Parking* parking , int i);
int Park(Parking *parking, Car car, Time time);
void park_control(void);

#endif
