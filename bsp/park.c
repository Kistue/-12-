#include "park.h"
#include "uart.h"

extern Parking parking[8];
extern Car car;
extern Time time;



int Parking_Space = 8;
int Remain_Parking = 5;


float charge;
float charge_VNBR = 3.5;
float charge_CNBR = 3.5;


#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

    return ch;
}

void Init_parking(Parking *parking)
{
    for (int i = 0; i < 8; i++)
    {
        strcpy(parking[i].car.id, "");
        strcpy(parking[i].car.type, "");
        parking[i].time.year = 0;
        parking[i].time.month = 0;
        parking[i].time.date = 0;
        parking[i].time.hour = 0;
        parking[i].time.minute = 0;
        parking[i].time.second = 0;
        parking[i].ifpark = 1;
        parking[i].location = i + 1;
    }
}

Time Init_Time(Time time)
{
    time.year = 0;
    time.date = 0;
    time.hour = 0;
    time.minute = 0;
    time.month = 0;
    time.second = 0;
    return time;
}

Car Init_Car(Car car)
{
    strcpy(car.id, "");
    strcpy(car.type, "");
    return car;
}

char *substring(char *Rx_data, int begin, int lenth)
{
    char *data = Rx_data;
    static char string[10];
    data = begin + data - 1;
    for (int i = 0; i < lenth; i++)
    {
        string[i] = *(data++);
    }
    return string;
}

char* splitString(const char* input, int start, int length) {
    if (input == NULL) {
        return NULL;
    }

    int inputLength = strlen(input);

    if (start < 0 || start >= inputLength || length <= 0 || (start + length) > inputLength) {
        return NULL;
    }

    char* result = (char*)malloc((length + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    strncpy(result, input + start, length);
    result[length] = '\0';

    return result;
}

int Analysic(char *Rx_data)
{
    char* type = splitString(Rx_data, 0, 4);
    char* id = splitString(Rx_data, 5, 4);
     if (type == NULL || id == NULL) {
        free(type);  // 在退出前释放内存
        free(id);    // 在退出前释放内存
        return 0;
    } 
    /* char type[5];
    char id[5]; */
    /* int year;
    int month;
    int date;
    int hour;
    int minute;
    int second; */
    
   /*  strcpy(type, splitString(Rx_data, 0, 4));
    strcpy(id, splitString(Rx_data, 5, 4)); */
    int year = atoi(splitString(Rx_data, 10, 2));
    int month = atoi(splitString(Rx_data, 12, 2));
    int date = atoi(splitString(Rx_data, 14, 2));
    int hour = atoi(splitString(Rx_data, 16, 2));
    int minute = atoi(splitString(Rx_data, 18, 2));
    int second = atoi(splitString(Rx_data, 20, 2));
    //__HAL_UART_FLUSH_DRREGISTER(&huart1);
    printf("RX2:%s\r\n" , Rx_data);
    
    
    printf("type:%s\r\n" , type);
    printf("id:%s\r\n" , id);
    printf("year:%d\r\n", year);
    printf("month:%d\r\n", month);
    printf("date:%d\r\n", date);
    printf("hour:%d\r\n", hour);
    printf("minute:%d\r\n", minute);
    printf("second:%d\r\n", second);  
    
    /* HAL_UART_Transmit_IT(&huart1, (uint8_t *)splitString(Rx_data, 0, 4), 4);
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"\r\n", strlen("\r\n"));
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)splitString(Rx_data, 5, 4), 4);
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"\r\n", strlen("\r\n"));
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)splitString(Rx_data, 10, 2), 2);
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"\r\n", strlen("\r\n"));
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)splitString(Rx_data, 12, 2), 2);
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"\r\n", strlen("\r\n"));
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)splitString(Rx_data, 14, 2), 2);
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"\r\n", strlen("\r\n"));
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)splitString(Rx_data, 16, 2), 2);
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"\r\n", strlen("\r\n"));
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)splitString(Rx_data, 18, 2), 2);
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"\r\n", strlen("\r\n"));
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)splitString(Rx_data, 20, 2), 2);
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"\r\n", strlen("\r\n"));  */
 
    // memset(Rx_data , 0 , sizeof(Rx_data));
    // HAL_UART_Transmit_IT(&huart1 , (uint8_t*)Rx_data , strlen(Rx_data));

    // HAL_UART_Transmit(&huart1 , "1\r\n" , strlen("1\r\n") , 1000);
    if ((abs(strcmp(type, "CNBR")) && abs(strcmp(type, "VNBR"))) == 1)
    {

        // HAL_UART_Transmit(&huart1 , "2\r\n" , strlen("2\r\n") , 1000);
        HAL_UART_Transmit(&huart1, "ERROR CAR TYPE\r\n", strlen("ERROR CAR TYPE\r\n") , 0xff);
        free(type);
        free(id);
        return 0;
    }
    // HAL_UART_Transmit(&huart1 , (uint8_t*)Rx_data , strlen(Rx_data) , 1000);
    if (month > 12 || date >= 31 || hour >= 24 || minute >= 60 || second >= 60)
    {
        // HAL_UART_Transmit(&huart1 , "3\r\n" , strlen("3\r\n") , 1000);
        HAL_UART_Transmit(&huart1, "ERROR TIME\r\n", strlen("ERROR TIME\r\n") , 0xff);
        free(type);
        free(id);
        return 0;
    }
    else
    {
        HAL_UART_Transmit(&huart1, "TRUE DATA\r\n", strlen("TRUE DATA\r\n") , 0xff);
        strcpy(car.type, type);
        strcpy(car.id, id);
        time.year = year;
        time.month = month;
        time.date = date;
        time.hour = hour;
        time.minute = minute;
        time.second = second;
        free(type);
        free(id);
    }
    return 1;
}

int go_out(Car car , Time time , Parking* parking)
{
    float charge_year;
    float charge_month;
    float charge_date;
    float charge_hour;
    float charge_minute;
    float charge_second;

    for(int i=0 ; i<Parking_Space ; i++)
    {
        
        if(parking[i].ifpark) continue;
        if(strcmp(car.id , parking[i].car.id) == 0)
        {
            if(strcmp("CNBR" , parking[i].car.type) == 0)
            {
                //CNBR计费
                charge_year = time.year - parking[i].time.year;
                charge_month = time.month - parking[i].time.month;
                charge_date = time.date - parking[i].time.date;
                charge_hour = time.hour - parking[i].time.hour;
                charge_minute = time.minute - parking[i].time.minute;
                charge_second = time.second - parking[i].time.second;
                if( (charge_minute + charge_second) >0 )
                {
                    charge_hour++;
                }
                charge = ( charge_year * 365 * 24 + charge_month * 30 * 24 + charge_date * 24 + charge_hour ) * charge_CNBR;
                parking[i].time.year = 0;
                parking[i].time.month = 0;
                parking[i].time.date = 0;
                parking[i].time.hour = 0;
                parking[i].time.minute = 0;
                parking[i].time.second = 0;
                parking[i].ifpark = 1;
                strcpy(parking[i].car.type , "");
                strcpy(parking[i].car.id , "");
                printf("Handle:%.2f\r\n" , charge);
                /* printf("\r\n");
                printf("type:%s\r\n" , parking[i].car.type);
                printf("id:%s\r\n" , parking[i].car.id);
                printf("year:%d\r\n", parking[i].time.year);
                printf("month:%d\r\n", parking[i].time.month);
                printf("date:%d\r\n", parking[i].time.date);
                printf("hour:%d\r\n", parking[i].time.hour);
                printf("minute:%d\r\n", parking[i].time.minute);
                printf("second:%d\r\n", parking[i].time.second);
                printf("ifpark:%d\r\n" , parking[i].ifpark);
                printf("location:%d\r\n" , parking[i].location); */
                return 1; //成功出去
            }

            if(strcmp("VNBR" , parking[i].car.type) == 0)
            {
                //VNBR计费
                charge_year = time.year - parking[i].time.year;
                charge_month = time.month - parking[i].time.month;
                charge_date = time.date - parking[i].time.date;
                charge_hour = time.hour - parking[i].time.hour;
                charge_minute = time.minute - parking[i].time.minute;
                charge_second = time.second - parking[i].time.second;
                if( (charge_minute + charge_second) >0 )
                {
                    charge_hour++;
                }
                parking[i].time.year = 0;
                parking[i].time.month = 0;
                parking[i].time.date = 0;
                parking[i].time.hour = 0;
                parking[i].time.minute = 0;
                parking[i].time.second = 0;
                parking[i].ifpark = 1;
                strcpy(parking[i].car.type , "");
                strcpy(parking[i].car.id , "");
                charge = ( charge_year * 365 * 24 + charge_month * 30 * 24 + charge_date * 24 + charge_hour ) * charge_VNBR;
                printf("Handle:%.2f\r\n" , charge);
                /* printf("\r\n");
                printf("type:%s\r\n" , parking[i].car.type);
                printf("id:%s\r\n" , parking[i].car.id);
                printf("year:%d\r\n", parking[i].time.year);
                printf("month:%d\r\n", parking[i].time.month);
                printf("date:%d\r\n", parking[i].time.date);
                printf("hour:%d\r\n", parking[i].time.hour);
                printf("minute:%d\r\n", parking[i].time.minute);
                printf("second:%d\r\n", parking[i].time.second);
                printf("ifpark:%d\r\n" , parking[i].ifpark);
                printf("location:%d\r\n" , parking[i].location); */
                return 1; //成功出去
            }
            return 0;
        }
    }
    return 0;
}

void ifpark_Init(Parking* parking)
{
    for(int i = 0; i<8 ; i++)
    {
        parking[i].ifpark = 1;
    }
}

int ifpark(Parking* parking , int i)
{
   if(parking[i].ifpark == 1)
   {
        return 1;
   }
   return 0;
}

int Park(Parking *parking, Car car, Time time)
{

    if(Remain_Parking <= 0)
    {
        HAL_UART_Transmit(&huart1 , "BUSY!\r\n" , strlen("BUSY!\r\n") , 0xff);
        return 0;
    }       

    for(int i = 0 ; i<Parking_Space ; i++)
    {
        
        if( !ifpark(parking , i) )
        {
            continue;
        }
        /* printf("type:%s\r\n" , parking[i].car.type);
        printf("id:%s\r\n" , parking[i].car.id);
        printf("year:%d\r\n", parking[i].time.year);
        printf("month:%d\r\n", parking[i].time.month);
        printf("date:%d\r\n", parking[i].time.date);
        printf("hour:%d\r\n", parking[i].time.hour);
        printf("minute:%d\r\n", parking[i].time.minute);
        printf("second:%d\r\n", parking[i].time.second);
        printf("ifpark:%d\r\n" , parking[i].ifpark);
        printf("location:%d\r\n" , parking[i].location); */

        strcpy(parking[i].car.type , car.type);
        strcpy(parking[i].car.id , car.id);
        parking[i].time.year = time.year;
        parking[i].time.month = time.month;
        parking[i].time.date = time.date;
        parking[i].time.hour = time.hour;
        parking[i].time.minute = time.minute;
        parking[i].time.second = time.second;
        parking[i].ifpark = 0;

        /* printf("\r\n");
        printf("type:%s\r\n" , parking[i].car.type);
        printf("id:%s\r\n" , parking[i].car.id);
        printf("year:%d\r\n", parking[i].time.year);
        printf("month:%d\r\n", parking[i].time.month);
        printf("date:%d\r\n", parking[i].time.date);
        printf("hour:%d\r\n", parking[i].time.hour);
        printf("minute:%d\r\n", parking[i].time.minute);
        printf("second:%d\r\n", parking[i].time.second);
        printf("ifpark:%d\r\n" , parking[i].ifpark);
        printf("location:%d\r\n" , parking[i].location); */
        

        HAL_UART_Transmit(&huart1 , "SUCCESS!\r\n" , strlen("SUCCESS!\r\n") , 0xff);
        return 1;
    }
    return 0;
}

void park_control(void)
{
    Analysic(Rx_data);  //分析数据
    if(go_out(car , time , parking) == 1)
    {
        return;
    }else
    {
        Park(parking , car , time);
    }  
}

