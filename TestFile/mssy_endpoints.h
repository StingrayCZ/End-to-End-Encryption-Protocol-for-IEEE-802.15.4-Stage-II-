/*
 * mssy_endpoints.h
 *
 * Created: 6.4.2017 15:02:44
 *  Author: Krajsa
 */ 


#ifndef MSSY_ENDPOINTS_H_
#define MSSY_ENDPOINTS_H_

bool appText(NWK_DataInd_t *ind);
bool appGet_Data_req(NWK_DataInd_t *ind);
bool appGet_Data_event(NWK_DataInd_t *ind);
bool appGet_Data_per(NWK_DataInd_t *ind);
bool appLEDswap(NWK_DataInd_t *ind);
bool appNeighbCoordinator(NWK_DataInd_t *ind);
bool appNeighbDisc(NWK_DataInd_t *ind);
bool appGetAddress(NWK_DataInd_t *ind);
#endif /* MSSY_ENDPOINTS_H_ */