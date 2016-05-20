#!/bin/sh
export CLASSPATH=`hadoop classpath --glob`
export LD_LIBRARY_PATH=/app/hdfs/lib/native:/app/jdk1.7/jre/lib/amd64/server

./hdfstest
