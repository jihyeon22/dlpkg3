#include <stdio.h>

#include "ftp_list.h"

ftp_server_info_t ftp_table[] =
{
	{
		.addr = "virtual.mdstec.com",
		.port = 21,
		.id = "iotdm",
		.pass = "dmiot"
	},
	{
		.addr = NULL,
		.port = 0,
		.id = NULL,
		.pass = NULL		
	},
};
