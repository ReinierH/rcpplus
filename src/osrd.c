/*
 * osrd.c
 *
 *  Created on: Sep 15, 2012
 *      Author: arash
 *
 *  This file is part of rcpplus
 *
 *  rcpplus is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  rcpplus is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with rcpplus.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <tlog/tlog.h>

#include "osrd.h"

typedef struct {
	unsigned char option;
	unsigned char reserved;
	unsigned short lease_time;
	unsigned char packet_len;
	unsigned short address;
	unsigned char opcode;
	unsigned char data_byte[3];
} osrd_packet;

static Funcptr_t send_data = &ptz_send;

static unsigned char checksum(unsigned char* data, int len)
{
	unsigned char sum = 0;
	for (int i=0; i<len; i++)
		sum += data[i];
	return (sum & 0x7f);
}

static int send_osrd(int line, int lease_time, int opcode, unsigned char* data, int data_len)
{
	unsigned short tmp16;
  unsigned char payload[OSRD_PACKET_SIZE];
	payload[0] = 0; // options : Currently no options used
	payload[1] = 0; // reserved
	tmp16 = htons(lease_time);
	memcpy(payload+2, &tmp16, 2);

	payload[4] = 0x80 + 4 + data_len; // number of bytes in the remainder of the packet

	payload[5] = 0;
	payload[6] = line; // address

	payload[7] = opcode;

	memcpy(payload+8, data, data_len);

	payload[8+data_len] = checksum(payload+4, data_len+4);

	int payload_length = 8 + data_len + 1;

	return send_data(payload, payload_length);
}

void osrd_init(Funcptr_t send_func)
{
	// initialize global send function
	send_data = send_func;
}

int osrd_move_right(int line, int lease, int speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.pan_right = 1;
	ptz.pan_speed = speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_move_left(int line, int lease, int speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.pan_left = 1;
	ptz.pan_speed = speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_move_up(int line, int lease, int speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.tilt_up = 1;
	ptz.tilt_speed = speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_move_down(int line, int lease, int speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.tilt_down = 1;
	ptz.tilt_speed = speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_move_up_right(int line, int lease, int pan_speed, int tilt_speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.tilt_up = 1;
	ptz.tilt_speed = tilt_speed;
	ptz.pan_right = 1;
	ptz.pan_speed = pan_speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_move_up_left(int line, int lease, int pan_speed, int tilt_speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.tilt_up = 1;
	ptz.tilt_speed = tilt_speed;
	ptz.pan_left = 1;
	ptz.pan_speed = pan_speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_move_down_right(int line, int lease, int pan_speed, int tilt_speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.tilt_down = 1;
	ptz.tilt_speed = tilt_speed;
	ptz.pan_right = 1;
	ptz.pan_speed = pan_speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_move_down_left(int line, int lease, int pan_speed, int tilt_speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.tilt_down = 1;
	ptz.tilt_speed = tilt_speed;
	ptz.pan_left = 1;
	ptz.pan_speed = pan_speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_move_stop(int line, int lease)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_zoom_in(int line, int lease, int speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.zoom_in = 1;
	ptz.zoom_speed = speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_zoom_out(int line, int lease, int speed)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.zoom_out = 1;
	ptz.zoom_speed = speed;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_focus_far(int line, int lease)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.focus_far = 1;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_focus_near(int line, int lease)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.focus_near = 1;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_iris_darker(int line, int lease)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.iris_darker = 1;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_iris_brighter(int line, int lease)
{
	VarSpeedPTZ ptz;
	memset(&ptz, 0, sizeof(VarSpeedPTZ));
	ptz.iris_brighter = 1;

	return send_osrd(line, lease, 5, (unsigned char*)&ptz, sizeof(VarSpeedPTZ));
}

int osrd_preposition_set(int line, int lease, unsigned short preposition_number)
{
	Preposition prep;
	memset(&prep, 0, sizeof(Preposition));
	prep.function_code = 4;
	prep.data_bit_lo = preposition_number & 0x03FF;
	prep.data_bit_hi = (preposition_number >> 7) & 0x07;

	return send_osrd(line, lease, 7, (unsigned char*)&prep, sizeof(prep));
}

int osrd_preposition_shot(int line, int lease, unsigned short preposition_number)
{
	Preposition prep;
	memset(&prep, 0, sizeof(Preposition));
	prep.function_code = 5;
	prep.data_bit_lo = preposition_number & 0x03FF;
	prep.data_bit_hi = (preposition_number >> 7) & 0x07;

	return send_osrd(line, lease, 7, (unsigned char*)&prep, sizeof(prep));
}
