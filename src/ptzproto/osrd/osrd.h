/*
 * ptz.h
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

#ifndef OSRD_H_
#define OSRD_H_

#define OSRD_PACKET_SIZE  16

typedef struct {
	unsigned char tilt_speed:4;
	unsigned char zoom_speed:3;
	unsigned char db1_res:1;

	unsigned char focus_far:1;
	unsigned char iris_darker:1;
	unsigned char iris_brighter:1;
	unsigned char pan_speed:4;
	unsigned char db2_res:1;

	unsigned char pan_right:1;
	unsigned char pan_left:1;
	unsigned char tilt_down:1;
	unsigned char tilt_up:1;
	unsigned char zoom_out:1;
	unsigned char zoom_in:1;
	unsigned char focus_near:1;
	unsigned char db3_res:1;
} VarSpeedPTZ;

typedef struct {
	unsigned char function_code:4;
	unsigned char data_bit_hi:3;
	unsigned char res1:1;

	unsigned char data_bit_lo:7;
	unsigned char res2:1;
} Preposition;

typedef int (*Funcptr_t)(unsigned char*, int);

void osrd_init(Funcptr_t sendptr);

int osrd_move_stop(int line, int lease);

int osrd_move_right(int line, int lease, int speed);
int osrd_move_left(int line, int lease, int speed);

int osrd_move_up(int line, int lease, int speed);
int osrd_move_down(int line, int lease, int speed);

int osrd_move_up_right(int line, int lease, int pan_speed, int tilt_speed);
int osrd_move_up_left(int line, int lease, int pan_speed, int tilt_speed);

int osrd_move_down_right(int line, int lease, int pan_speed, int tilt_speed);
int osrd_move_down_left(int line, int lease, int pan_speed, int tilt_speed);

int osrd_zoom_in(int line, int lease, int speed);
int osrd_zoom_out(int line, int lease, int speed);

int osrd_focus_far(int line, int lease);
int osrd_focus_near(int line, int lease);

int osrd_iris_darker(int line, int lease);
int osrd_iris_brighter(int line, int lease);

int osrd_preposition_set(int line, int lease, unsigned short preposition_number);
int osrd_preposition_shot(int line, int lease, unsigned short preposition_number);

#endif /* OSRD_H_ */
