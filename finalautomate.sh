#!/bin/bash
# Make all scripts executable
chmod +x finalreport.sh
chmod +x finalalerts.sh
chmod +x finalscript.sh

# Dynamically fetch DBUS_SESSION_BUS_ADDRESS and DISPLAY
USER_DBUS_SESSION_BUS_ADDRESS=$(dbus-launch | grep 'DBUS_SESSION_BUS_ADDRESS' | cut -d '=' -f2-)
USER_DISPLAY=$(echo $DISPLAY)

# dynamic variables
SCRIPT_TO_SCHEDULE_one="DBUS_SESSION_BUS_ADDRESS=$USER_DBUS_SESSION_BUS_ADDRESS DISPLAY=$USER_DISPLAY cd /home/oem/Desktop/finalprojectofcew && ./finalreport.sh"
CRON_SCHEDULE_one="10 17 * * 1"
SCRIPT_TO_SCHEDULE_two="DBUS_SESSION_BUS_ADDRESS=$USER_DBUS_SESSION_BUS_ADDRESS DISPLAY=$USER_DISPLAY cd /home/oem/Desktop/finalprojectofcew && ./finalalerts.sh"
CRON_SCHEDULE_two="20 * * * *"
SCRIPT_TO_SCHEDULE_three="cd /home/oem/Desktop/finalprojectofcew && ./finalscript.sh"
CRON_SCHEDULE_three="55 * * * *"

# Schedule the job in crontab
(crontab -l 2>/dev/null; echo "$CRON_SCHEDULE_one $SCRIPT_TO_SCHEDULE_one") | crontab - >/dev/null 2>&1

# (crontab -l 2>/dev/null; echo "$CRON_SCHEDULE_one $SCRIPT_TO_SCHEDULE_one") | crontab - >/dev/null 2>&1

(crontab -l 2>/dev/null; echo "$CRON_SCHEDULE_two $SCRIPT_TO_SCHEDULE_two") | crontab - >/dev/null 2>&1

(crontab -l 2>/dev/null; echo "$CRON_SCHEDULE_three $SCRIPT_TO_SCHEDULE_three") | crontab - >/dev/null 2>&1





