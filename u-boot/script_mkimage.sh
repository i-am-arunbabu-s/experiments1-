#!/bin/sh
 
if [ ! -f "$1" ] || [ $# -lt 2 ]
then
        echo "Usage: $0 SCRIPTNAME OUTPUTNAME"
        exit 1
fi
 
mkimage -T script -C none -A arm -n 'Boot Script' -d $1 $2
