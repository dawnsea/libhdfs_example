#include <stdio.h>
#include <stdlib.h>

#include "hdfs.h"


int main()
{

    hdfsFS fs;
    hdfsFileInfo *fi;
    hdfsFile rfile;
    struct hadoopRzOptions *opts = NULL;
    struct hadoopRzBuffer *buffer = NULL;

    int i;
    int fnum;
    char *temp;

    printf("hello hdfs\n");

    fs = hdfsConnect("default", 0);
    fi = hdfsListDirectory(fs, "reco_log_tracking_file" , &fnum);

    for (i = 0; i < fnum; i++) {

        printf("%02d:%s, %ld\n", i, (fi + i)->mName, (fi + i)->mSize);
        rfile = hdfsOpenFile(fs, "reco_log_tracking_file/000000_0", O_RDONLY, 0, 0, 0);

        opts = hadoopRzOptionsAlloc();
        hadoopRzOptionsSetByteBufferPool(opts, ELASTIC_BYTE_BUFFER_POOL_CLASS);
        hadoopRzOptionsSetSkipChecksum(opts, 0);
        buffer = hadoopReadZero(rfile, opts, (fi + i)->mSize);

        printf("보고된 버퍼 크기      = %ld\n", (long)((fi + i)->mSize));
        printf("실제로 읽은 버퍼 크기 = %ld\n", (long)(hadoopRzBufferLength(buffer)));

        temp = hadoopRzBufferGet(buffer);
        temp[100] = 0;

        printf("버퍼 = %s\n", temp);
        hadoopRzBufferFree(rfile, buffer);
        hadoopRzOptionsFree(opts);
        hdfsCloseFile(fs, rfile);

    }

#if 0
    rfile = hdfsOpenFile(fs, "reco_log_tracking_file/000000_0", O_RDONLY, 0, 0, 0);
    if (!rfile) {
        printf("오픈 실패\n");
    }
    rsize = 4096;
    rsize = hdfsRead(fs, rfile, (void *)temp, rsize);

    hdfsCloseFile(fs, rfile);
    temp[4096] = 0;

    printf("buf = %s", temp);
#endif
    hdfsDisconnect(fs);

    exit(0);

}
