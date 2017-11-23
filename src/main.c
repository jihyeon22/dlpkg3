#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "update_api.h"
#include "file_check.h"
#include "common.h"
#include "pack_list.h"
#include "update.h"

#include <logd_rpc.h>
#include <mdsapi/mds_api.h>

#define LOG_TARGET eSVC_MODEL

void dlpkg_poweroff()
{
	while(1)
	{
		mds_api_poweroff();
		sleep(10);
	}
}

int main(int argc, char** argv)
{
	char target_file[255] = {0};
	int i = 0;

	int is_downloaded = 0;
	int is_normal = 1;
	int n_retry = 0;

	logd_init();

    printf("dlpkg3 start!! [%s]\r\n", __DATE__);

    LOGE(LOG_TARGET, "dlpkg3 start!! [%s]\r\n", __DATE__);

	// do not check.. 
	/*
    while(1)
    {
        if ( mds_api_get_netstate(CHK_NETWORK_INTERFACE) == DEFINES_MDS_API_OK)
            break;

        sleep(1);
        LOGE(LOG_TARGET, "dlpkg3 wait netstat!! [%s]\r\n", __DATE__);
        printf("dlpkg3 wait netstat!! [%s]\r\n", __DATE__);
    }
	*/
	
	while(1)
	{
		is_downloaded = 0;
		for(i = 0; package_list[i].remotePath != NULL  ; i++)
		{
			if(check_package(package_list[i]) >= 0)
			{
                LOGI(LOG_TARGET, "package ok! [0]%s\n", package_list[i].localFiles[0].localPath);
				continue;
			}
			
			is_normal = 0;
			
			if(update_ftp_download(package_list[i].remotePath, target_file) == UPDATE_FAILURE)
			{
				continue;
			}
			
			extract_gz(target_file, package_list[i].unzipRoot);
			
			del_temp_dir();
			
			is_downloaded = 1;
		}
		
		if(is_normal == 1)
		{
			return 0;
		}

		is_normal = 1;
		for(i = 0; package_list[i].remotePath != NULL ; i++)
		{
			if(check_package(package_list[i]) < 0)
			{
				is_normal = 0;
				break;
			}

			LOGI(LOG_TARGET, "package ok! [0]%s\n", package_list[i].localFiles[0].localPath);
		}
		
		if(is_normal)
		{
			if(is_downloaded)
			{
				dlpkg_poweroff();
			}
			return 0;
		}
		
		sleep(RETRY_SECS);
	}
}
