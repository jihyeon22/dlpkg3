#include <stdio.h>
#include "file_check.h"

packageInfo_t package_list[] =
{
	{
		.remotePath = "/home/dlpkg/TL500/libcurl.4.3.0-openssl.tar.gz",
		.unzipRoot = "/system/mds/",
		.localFiles[0].localPath = "/system/mds/usr/lib/libcurl.so",
		.localFiles[0].size = 319933,
		.localFiles[1].localPath = "/system/mds/usr/lib/libcurl.so.4",
		.localFiles[1].size = 319933,
		.localFiles[2].localPath = "/system/mds/usr/lib/libcurl.so.4.3.0",
		.localFiles[2].size = 319933,
		.localFiles[3].localPath = NULL,
		.localFiles[3].size = 0
	},
    /*
	{
		.remotePath = "/home/LIBS/mosquitto-openssl.1.4.14.tar.gz",
		.unzipRoot = "/system/mds/",
		.localFiles[0].localPath = "/usr/lib/libmosquitto.so.1",
		.localFiles[0].size = 172576,
		.localFiles[3].localPath = NULL,
		.localFiles[3].size = 0
	},
    */
	{
		.remotePath = NULL,
		
		.localFiles[0].localPath = NULL,
		.localFiles[0].size = 0
	}	
};
