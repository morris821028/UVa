#!/bin/bash

TEXT_RED=`tput setaf 1`
TEXT_GREEN=`tput setaf 2`
TEXT_RESET=`tput sgr0`
CONFIG_FILE=nvvp.cfg

if [ ! -f $CONFIG_FILE ];
then
	echo "[ERROR] Profile config file ${TEXT_RED}nvvp.cfg${TEXT_RESET} does not exist."
	exit 1
fi


COMPUTE_PROFILE=1 COMPUTE_PROFILE_CONFIG=${CONFIG_FILE} $@

if [ $? -eq 0 ];
then
	echo "[INFO] ${TEXT_GREEN}Profiler Successed.${TEXT_RESET}"
else
	echo "[ERROR] ${TEXT_RED}Usage: ./nvprof.sh <execute-command>${TEXT_RESET}"
	exit 1
fi

echo "[INFO] Starting change opencl_profile ..."
find . -name 'opencl_profile*.log' | while read LOGFILE;
do
	echo "[INFO] Find OpenCL profile log ${LOGFILE}"
	TARGET=${LOGFILE//opencl/cuda};
	LOGLINE=$(wc -l < "$LOGFILE");
	if [ "$LOGLINE" -gt "7" ]
	then
		sed -e 's/OPENCL_/CUDA_/g' \
			-e 's/ndrange/grid/g' \
			-e 's/workitem/thread/g' \
			-e 's/workgroupsize/threadblocksize/g' \
			-e 's/stapmemperworkgroup/stasmemperblock/g' \
			$LOGFILE > $TARGET;
	fi;
done;

cat cuda_profile_*.log > nvvp.log
if [ $? -eq 0 ];
then
	echo "[INFO] Create ${TEXT_GREEN}nvvp.log${TEXT_RESET} Successed"
else
	echo "[ERROR] Create profile log Fail"
	exit 1
fi

rm cuda_profile_*.log opencl_profile*.log
echo "[INFO] Now, use NVVP and import OpenCL profile log." 
