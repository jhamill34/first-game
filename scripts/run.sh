#!/bin/bash 

NAME=$1

shift 1

./build/apps/$NAME/${NAME}App $@
