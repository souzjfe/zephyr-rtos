#!/bin/bash

cd ~/zephyrproject
source .venv/bin/activate
west flash -d ~/Developments/zephyr_app/build/

