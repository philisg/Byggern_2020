/**
 * @file CAN.h
 * @author TTK4155 2020 Group 28
 * @date 17 nov 2020
 * @brief File containing top level drivers for MCU based CAN bus communication.
 */

#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>
#include "can_controller.h"

int CAN_RXcmplt(void);
void CAN_init(uint8_t mode);
void CAN_send(CAN_MESSAGE* TX_packet);
void CAN_receive(int RX_buffer, CAN_MESSAGE* RX_packet);
int CAN_TXcomplete(uint8_t buffer_number);
uint8_t CAN_error(void);
CAN_MESSAGE CAN_handler(void);
int8_t CAN_read(CAN_MESSAGE* RX_packet);

#endif /* CAN_H_ */
