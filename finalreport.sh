#!/bin/bash
export DISPLAY=:0
export DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/$(id -u)/bus"
# Check if today is Monday
if [ "$(date +%u)" -ne 1 ]; then
  echo "Today is not Monday. Report generation skipped."
  exit 0
fi

# Define input JSON file
INPUT_FILE="weather_data_array.json"

# Parse dates from last Monday to Sunday
TODAY=$(date +%Y-%m-%d)
LAST_MONDAY=$(date -d "last monday" +%Y-%m-%d)
LAST_SUNDAY=$(date -d "last sunday" +%Y-%m-%d)

# Extract relevant data using jq
REPORT=$(jq --arg last_monday "$LAST_MONDAY" --arg last_sunday "$LAST_SUNDAY" '
  map(select(.date >= $last_monday and .date <= $last_sunday))' "$INPUT_FILE")

# Check if report is empty
if [ "$(echo "$REPORT" | jq length)" -eq 0 ]; then
  REPORT="No data available for the specified period."
else
  # Format report for display
  REPORT=$(echo "$REPORT" | jq -r '
    .[] | "Date: \(.date)
Location: \(.location.name), \(.location.region), \(.location.country)
Weather: \(.current_weather.condition)
Temperature: \(.current_weather.temperature_c)°C
Humidity: \(.current_weather.humidity)%"
  ')
fi

# Display the report using zenity
zenity --info --title="Weekly Weather Report" --text="Weather Report (Last Monday to Sunday)\n\n$REPORT"
