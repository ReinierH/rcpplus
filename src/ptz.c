/*
 * ptz.c
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
#include <tlog/tlog.h>

#include "ptz.h"
#include "rcpdefs.h"
#include "rcpcommand.h"

#define PTZ_LEASETIME	2

int ptz_send(unsigned char* data, int size) {
	rcp_packet ptz_req;

	init_rcp_header(&ptz_req, 0, RCP_COMMAND_CONF_RCP_TRANSFER_TRANSPARENT_DATA, RCP_COMMAND_MODE_WRITE, RCP_DATA_TYPE_P_OCTET);
	ptz_req.numeric_descriptor = 1;

	ptz_req.payload[0] = 0x00; // options
	ptz_req.payload[1] = 0x00; // reserved
	unsigned short tmp = htons(PTZ_LEASETIME);
	memcpy(ptz_req.payload+2, &tmp, 2);

	// copy payload to rcp packet
	memcpy((void*)&ptz_req.payload+4, data, size);
	ptz_req.payload_length = size+4;

	rcp_packet* ptz_resp = rcp_command(&ptz_req);

	if (ptz_resp == NULL)
		goto error;
	if (ptz_resp->payload[0] == 0)
	{
		TL_ERROR("access to serial port denied");
		goto error;
	}

	return 0;

	error:
	TL_ERROR("ptz_send()");
	return -1;
}

int ptz_available(int line) {
	rcp_packet ptz_req;

	init_rcp_header(&ptz_req, 0, RCP_COMMAND_CONF_PTZ_CONTROLLER_AVAILABLE, RCP_COMMAND_MODE_READ, RCP_DATA_TYPE_F_FLAG);
	ptz_req.numeric_descriptor = line;

	rcp_packet* ptz_resp = rcp_command(&ptz_req);
	if (ptz_resp == NULL)
		goto error;

	return ptz_resp->payload[0];

error:
	TL_ERROR("ptz_available()");
	return 0;
}
