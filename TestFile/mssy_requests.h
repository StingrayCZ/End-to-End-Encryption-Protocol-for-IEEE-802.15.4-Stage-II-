/*
 * mssy_requests.h
 *
 * Created: 6.4.2017 16:11:46
 *  Author: Krajsa
 */ 



#ifndef MSSY_REQUESTS_H_
#define MSSY_REQUESTS_H_

void Req_NeighbDisc();
void Req_LED(int addr,uint8_t LED, uint8_t stav);
void Req_text(int dest);
void Req_Data(int addr,uint8_t data, uint8_t typ);
void Send_Data_Event(int addr,uint8_t data, uint8_t typ);
void Send_Data_Neighbors();
uint16_t Req_Addr();

#endif /* MSSY_REQUESTS_H_ */