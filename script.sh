#!/bin/bash
s=$(curl "http://api.weatherapi.com/v1/current.json?key=d8170b5ec9f84e669bf123724240311&q=karachi")
f=$(echo "$s" | sed 's/"/\\"/g')
# echo $f
echo $f >> finalrawdata.json
echo >> finalrawdata.json
echo $f > temporaryfile.txt



