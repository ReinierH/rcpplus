/*
 * test_ptz.c
 *
 *  Created on: Sep 15, 2012
 *      Author: arash
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <tlog/tlog.h>

#include "rcpdefs.h"
#include "rcpplus.h"
#include "rcpcommand.h"
#include "ptz.h"
#include "pelcod.h"


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "%s <ip>", argv[0]);
		return 0;
	}
	tlog_init(TLOG_MODE_STDERR, TLOG_INFO, NULL);

	rcp_connect(argv[1]);

	start_event_handler();

	client_register(RCP_USER_LEVEL_SERVICE, "service", RCP_REGISTRATION_TYPE_NORMAL, RCP_ENCRYPTION_MODE_PLAIN);

	if (ptz_available(1) == 0)
	{
		TL_INFO("ptz is not available for this camera");
		//return 0;
	}
	pelcod_init(&ptz_send);

  printf("moving camera up...\n");
	pelcod_move_up(0x01, 0x3f);
	sleep(1);
	pelcod_move_stop(0x01);
	sleep(2);

  printf("moving camera down...\n");
	pelcod_move_down(0x01, 0x3f);
	sleep(1);
	pelcod_move_stop(0x01);
	sleep(2);

  printf("moving camera left...\n");
	pelcod_move_left(0x01, 0x3f);
	sleep(1);
	pelcod_move_stop(0x01);
	sleep(2);

  printf("moving camera right...\n");
	pelcod_move_right(0x01, 0x3f);
	sleep(1);
	pelcod_move_stop(0x01);
	sleep(2);

  printf("moving camera to preset 6...\n");
	pelcod_goto_preset(0x01, 6);
	sleep(2);

	stop_event_handler();

	return 0;
}
