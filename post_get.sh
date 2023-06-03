#!/bin/bash

ADDRESS=0.0.0.0:8091/lrucache

curl -H "Content-Type: application/json" -X POST -d '{"key":1,"value":1}' $ADDRESS; echo
curl -H "Content-Type: application/json" -X POST -d '{"key":2,"value":2}' $ADDRESS; echo
curl -H "Content-Type: application/json" -X POST -d '{"key":3,"value":3}' $ADDRESS; echo

curl -H "Content-Type: application/json" -X GET $ADDRESS?key=1; echo
curl -H "Content-Type: application/json" -X GET $ADDRESS?key=2; echo
curl -H "Content-Type: application/json" -X GET $ADDRESS?key=3; echo
curl -H "Content-Type: application/json" -X GET $ADDRESS?key=4; echo
