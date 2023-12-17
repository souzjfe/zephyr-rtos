#!/bin/bash

cd ~/zephyrproject
source .venv/bin/activate
#west build -b nucleo_g431rb ~/Developments/zephyr_app -d ~/Developments/zephyr_app/build
west build -p always -b nucleo_g474re ~/Developments/zephyr_app -d ~/Developments/zephyr_app/build

