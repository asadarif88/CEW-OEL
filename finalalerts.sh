#!/bin/bash
export DISPLAY=:0
export DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/$(id -u)/bus"
json_data=$(curl "http://api.weatherapi.com/v1/current.json?key=d8170b5ec9f84e669bf123724240311&q=karachi")
temp_c=$(echo "$json_data" | grep -o '"temp_c":[0-9.]*' | awk -F':' '{print int($2)}')
month=$(date +"%m") # Fetch the current month (e.g., 01 for January, 11 for November)
echo "$temp_c"
case $month in
    12|01|02) # December, January, February (Winter)
        limit=15
        if [ "$temp_c" -lt "$limit" ]; then
        echo "ALERT: The temperature is ${temperature}°C, which is very low for this month.Very Cold! Be at warm."
        fi
        ;;
    03|04|05) # March, April, May (Spring)
        limit=38
        if [ "$temp_c" -gt "$limit" ]; then
        DISPLAY=:0 notify-send "ALERT: The temperature is ${temp_c}°C, which is very hot for this current month."
        fi
        ;;
    06|07|08) # June, July, August (Summer)
        limit=35
        if [ "$temp_c" -gt "$limit" ]; then
        DISPLAY=:0 notify-send "ALERT: The temperature is ${temp_c}°C, which is very hot for this month."
        fi
        ;;
    09|10|11) # September, October, November (Autumn)
        limit=34
        lowlimit=20
        if [ "$temp_c" -gt "$limit" ]; then
        DISPLAY=:0 notify-send "ALERT: The temperature is ${temp_c}°C, which is very hot for this month."
        elif [ "$temp_c" -lt "$lowlimit" ]; then
        DISPLAY=:0 notify-send "ALERT: The temperature is ${temp_c}°C, which is very cold for this month."
        fi
        ;;
    *) 
        echo "Unknown month."
        exit 1
        ;;
esac
