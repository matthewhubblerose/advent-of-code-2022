#!/usr/bin/env bash

DAY_NUMBER=${1}
if [ -z "${DAY_NUMBER}" ];
then
    DAY_NUMBER=$(date +%d)
fi
printf -v PADDED_DAY_NUMBER "%02d" ${DAY_NUMBER}

cp -r ./template "./day-${PADDED_DAY_NUMBER}"
open -na "CLion.app" --args "./day-${PADDED_DAY_NUMBER}"
