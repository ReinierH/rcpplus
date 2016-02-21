/* 
* @Author: reinierh
* @Date:   2016-01-09 17:41:23
* @Last Modified by:   reinierh
* @Last Modified time: 2016-01-11 00:32:48
*/
#include <inttypes.h>

#include "ptz.h"
#include "pelcod_defs.h"
#include "pelcod.h"

static Funcptr_t send_data = &ptz_send;

static unsigned char calc_checksum(unsigned char* data, int size) {
	short i;
	unsigned int total = 0;
	for(i = 0; i < size; i++)
		total += data[i];

	return total;
}

/* globally used functions */
void pelcod_init(Funcptr_t ptr) {
	send_data = ptr;
}

static int pelcod_send(unsigned char address, unsigned short command, unsigned short payload) {
	unsigned char buffer[PELCOD_MSG_SIZE];	

	buffer[0] = 0xFF;						// preamble
	buffer[1] = address;					// device address
	buffer[2] = (command & 0xFF00) >> 8;	// command 1
	buffer[3] = (command & 0xFF);			// command 2
	buffer[4] = (payload & 0xFF00) >> 8;	// data 1
	buffer[5] = (payload & 0xFF);			// data 2 
	buffer[6] = calc_checksum(buffer+1, PELCOD_MSG_SIZE - 2);

	send_data(buffer, PELCOD_MSG_SIZE);

	return(1);
}

/* Standard pelcod functions */
int pelcod_move_right(unsigned char address, unsigned short speed) {
  return pelcod_send(address, PELCOD_STD_RIGHT, (speed & 0xFF) << 8);
}

int pelcod_move_left(unsigned char address, unsigned short speed) {
  return pelcod_send(address, PELCOD_STD_LEFT, (speed & 0xFF) << 8);
}

int pelcod_move_up(unsigned char address, unsigned short speed) {
  return pelcod_send(address, PELCOD_STD_UP, speed);
}

int pelcod_move_down(unsigned char address, unsigned short speed) {
  return pelcod_send(address, PELCOD_STD_DOWN, speed);
}

int pelcod_zoom_far(unsigned char address) {
	return pelcod_send(address, PELCOD_STD_FOC_FAR, 0x3f);
}

int pelcod_zoom_near(unsigned char address) {
	return pelcod_send(address, PELCOD_STD_FOC_NEAR, 0x3f);
}

int pelcod_move_stop(unsigned char address) {
	return pelcod_send(address, 0x00, 0x00);
}

/* extended pelcod functions */
int pelcod_goto_preset(unsigned char address, unsigned short preset) {
	return pelcod_send(address, PELCOD_EXT_PRE_TO, preset);
}

int pelcod_set_zoom_speed(unsigned char address, unsigned short speed) {
	return pelcod_send(address, PELCOD_EXT_ZOO_SPE_SET, speed);
}

int pelcod_set_focus_speed(unsigned char address, unsigned short speed) {
	return pelcod_send(address, PELCOD_EXT_FOC_SPE_SET, speed);
}

int pelcod_move_around(unsigned char address) {
	return pelcod_send(address, PELCOD_EXT_FLIP, 21);
}

int pelcod_write_str(unsigned char address, const unsigned char* str) {
	int i, res;
	for(i = 0; i < 28 && str[i] != '\0'; i++) {
		unsigned short payload = ((i << 8) & 0xFF00) || str[i] & 0xFF;
		res = pelcod_send(address, PELCOD_EXT_CHAR_WR, payload); 

		if(res <= 0) 
			return(res);
	}

	return(res);
}

