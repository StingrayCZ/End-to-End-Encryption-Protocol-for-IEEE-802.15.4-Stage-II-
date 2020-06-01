/*
 * mssy_functions.h
 *
 * Created: 6.4.2017 16:13:41
 *  Author: Krajsa
 */ 


#ifndef MSSY_FUNCTIONS_H_
#define MSSY_FUNCTIONS_H_

void BoardInit();
void HAL_UART_SendString(char *s);
void HAL_UART_SendInt(int cislo);
//void appSendDataU(int Dest_Addr, int App_end, void *data,int delka);
void measure(void);

#endif /* MSSY_FUNCTIONS_H_ */