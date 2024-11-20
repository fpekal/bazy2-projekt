#!/usr/bin/env bash

mkdir -p backup
cp -f pony.db backup/pony_$(date +%Y-%m-%d_%H-%M-%S).db
