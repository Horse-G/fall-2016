#!/bin/bash

HNAME=cunix.cc.columbia.edu
ITER=5


function usage {
	echo "USAGE: ipstuff.sh: [ HNAME | HNAME ITER ]"
	exit 1
}

function oneip {
	if host ${1} > /dev/null
	then
		host ${1} | grep -w 'has address' | head -n 1 | cut -d " " -f 4
	else
		echo NA;
	fi
}

function ipdate {
	date +'%s'
}

function ipname {
	if nslookup ${1} > /dev/null
	then
		nslookup ${1} | head -n 1 | tr -d '\t' | cut -d ":" -f 2
	else
		echo NA;
	fi
}

function myipfile {
	grep $(hostname) /etc/hosts | head -n 1 | awk '{print $1}'
}

if [ "$#" -eq 1 ]
then
	HNAME=$1
elif [ "$#" -eq 2 ]
then
	HNAME=$1
	ITER=$2
elif [ "$#" -gt 2 ]
then
	usage
	exit $?
fi

seq 1 ${ITER:=5} >/dev/null 2>&1 || usage
if [ "$?" -ne 0 ]
then
	exit $?
fi

echo "UID, DATE, MYIP-FROM-FILE, MY-DNS, HOSTQUERY, RESP-FROM-DNS";
for i in $(seq 1 $ITER);
do
	echo "$(id -u),$(ipdate),$(myipfile),$(ipname ${HNAME}),${HNAME},$(oneip ${HNAME})";
	# lets have a rest for 5 seconds
	sleep 5;
done
