#include <stdio.h>
//#include <dlfcn.h>
#include <string.h>
#include <unistd.h>
#include <logd_rpc.h>

#include "file_check.h"
#include "update_api.h"

#include "common.h"

#define LOG_TARGET eSVC_MODEL


#define RETRY_OPEN_FILE 3

int check_file(fileInfo_t file_info)
{
	void * lib_handle = NULL;
	int size = 0;
	int n_retry = 0;
	
	n_retry = RETRY_OPEN_FILE;
	while(n_retry--)
	{
		size = download_size_get(file_info.localPath);
		
		if(size == file_info.size)
		{
			LOGI(LOG_TARGET, "size ok!\n");
			break;
		}
		
		if(size != file_info.size)
		{
			LOGE(LOG_TARGET, "mismatch size %s org:%d cur:%d\n", file_info.localPath, file_info.size, size);
		}
		
		usleep(100000);
    }
    
	if(n_retry < 0)
	{
		LOGE(LOG_TARGET, "final mismatch size %s org:%d cur:%d\n", file_info.localPath, file_info.size, size);
		return -1;
	}
    
    // alltype file..
    // not only library file..
    /*
	if(strstr(file_info.localPath, ".so") == NULL)
	{
		return 0;
	}

	lib_handle = dlopen(file_info.localPath, RTLD_NOW);
	if(lib_handle == NULL)
	{
		LOGI(LOG_TARGET, "dl open error! %s\n", file_info.localPath);
		return -1;
	}
	dlclose(lib_handle);
	LOGI(LOG_TARGET, "dlopen ok!\n");
    */
    
	return 0;
}

int check_package(packageInfo_t pack_info)
{
	int i = 0;
	int ret = 0;
	
	for(i=0; pack_info.localFiles[i].localPath != NULL; i++)
	{
		ret = check_file(pack_info.localFiles[i]);
		if(ret < 0)
		{
			return -1;
		}
	}
	
	return 0;
}
