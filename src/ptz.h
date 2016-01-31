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

#ifndef PTZ_H_
#define PTZ_H_

#include "rcpplus.h"

#define RCP_COMMAND_CONF_RCP_TRANSFER_TRANSPARENT_DATA	0xffdd
#define RCP_COMMAND_CONF_PTZ_CONTROLLER_AVAILABLE	0x0a51

int ptz_send(unsigned char* data, int size);

#endif /* PTZ_H_ */
