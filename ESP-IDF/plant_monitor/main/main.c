#include <stdio.h>
#include "wifi_sta_init.h"
#include "uart_init.h"
#include "tcp_server.h"

//-----------------------------------------------------------------
//freertos初始化函数
TaskHandle_t test1;
extern void test1Code(void *pvParameters);

//-----------------------------------------------------------------
//定义芯片
//#define ESP32_C6

int i = 0;
void app_main(void)
{
	 uart_init();
	 wifi_init_sta();
	 for(i = 0;i<60;i++)uart_write_bytes(ECHO_UART_PORT_NUM, (const char *) sta_ip, strlen(sta_ip));
	 vTaskDelay(100/portTICK_PERIOD_MS); //等待1s
	 tcp_server_init();
	 xTaskCreatePinnedToCore(test1Code, "test1", 10000, NULL, 1, &test1, 1);
}

extern int sock;


char combine[40];
char receive[10];
char receive_f[1];
int  rec_Count;
int  rec_flag;
void test1Code(void *pvParameters)
{
    while(1)
    {
		memset(receive,0,sizeof(receive));
		
		uart_read_bytes(ECHO_UART_PORT_NUM, receive_f, 1, 5 / portTICK_PERIOD_MS);
		if (receive_f[0] == 'h')
		{
			strcat(receive,receive_f);
			for(rec_Count = 1;rec_Count < 100;rec_Count++)
			{
				receive_f[0] = 0;
				uart_read_bytes(ECHO_UART_PORT_NUM, receive_f, 1, 5 / portTICK_PERIOD_MS);
				strcat(receive,receive_f);
				if (receive_f[0] == '~' && rec_flag == 2)
				{
					rec_flag = 0;
					break;
				}
				if(receive_f[0] == '~' && rec_flag == 1)rec_flag = 2;
				if(receive_f[0] == '~' && rec_flag == 0)rec_flag = 1;
			}
		}
		send(sock, receive, strlen((char *)receive), 0);
		
		uart_write_bytes(ECHO_UART_PORT_NUM, (const char *) sta_ip, strlen(sta_ip));

		vTaskDelay(10/portTICK_PERIOD_MS); //等待1s
    }
}
