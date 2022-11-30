#!/usr/bin/env bash

DAY_NUMBER=${1}
if [ -z "${DAY_NUMBER}" ];
then
    DAY_NUMBER=$(date +%d)
fi
printf -v PADDED_DAY_NUMBER "%02d" ${DAY_NUMBER}

if [ -z "${SESSION_ID}" ];
then
    echo "Enter session ID:"
    read SESSION_ID
fi
curl -H "cookie: session=${SESSION_ID}" "https://adventofcode.com/2022/day/${DAY_NUMBER}/input" > "./day-${PADDED_DAY_NUMBER}/input.txt"

