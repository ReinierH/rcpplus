/* 
* @Author: reinierh
* @Date:   2016-01-09 17:41:23
* @Last Modified by:   reinierh
* @Last Modified time: 2016-01-11 00:32:48
*/
#include <inttypes.h>

#include "pelcod.h"

static Funcptr_t send_data;

unsigned char calc_checksum(unsigned char* data, int size) {
	short i;
	unsigned char total;
	for(i = 0; i < size; i++)
		total += data[i];

	return (total % 256);
}

/* globally used functions */
void pelcod_init(Funcptr_t ptr) {
	send_data = ptr;
}

int pelcod_send(unsigned char address, short command, short payload) {
	unsigned char buffer[PELCOD_MSG_SIZE];	

	buffer[0] = 0xFF;						// preamble
	buffer[1] = address;					// device address
	buffer[2] = (command & 0xFF);			// command 1
	buffer[3] = (command & 0xFF00) >> 8;	// command 2
	buffer[4] = (payload & 0xFF);			// data 1 
	buffer[5] = (payload & 0xFF00) >> 8;	// data 2
	buffer[6] = calc_checksum(buffer+1, PELCOD_MSG_SIZE - 2);

	send_data(buffer, PELCOD_MSG_SIZE);
}

/* Standard pelcod functions */
int pelcod_move_right(unsigned char address, int speed) {
  return pelcod_send(address, PELCOD_STD_RIGHT, (UINT8_MAX / 100) * speed);
}

int pelcod_move_left(unsigned char address, int speed) {
  return pelcod_send(address, PELCOD_STD_LEFT, (UINT8_MAX / 100) * speed);
}

int pelcod_move_up(unsigned char address, int speed) {
  return pelcod_send(address, PELCOD_STD_UP, (UINT8_MAX / 100) * speed);
}

int pelcod_move_down(unsigned char address, int speed) {
  return pelcod_send(address, PELCOD_STD_UP, (UINT8_MAX / 100) * speed);
}




