#!/bin/sh
./my_otp < messageA.txt > mA.enc -k keyfile16K.key

./my_otp < messageB.txt > mB.enc -k keyfile16K.key

./my_otp < mA.enc > mA.txt -k keyfile16K.key

./my_otp < mB.enc > mB.txt -k keyfile16K.key

if diff mA.txt messageA.txt; then : ; else echo FAILED;  exit 1 ; fi

if diff mB.txt messageB.txt; then : ; else echo FAILED ; exit 1 ; fi

rm -f mA* mB*
echo PASSED
exit 0
