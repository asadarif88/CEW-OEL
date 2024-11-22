# Integrated Environmental Monitoring System

## Introduction
The Integrated Environmental Monitoring System is designed to provide real-time monitoring of environmental conditions such as temperature, humidity, and air quality. The system retrieves data from a weather API, processes and parses it using C language, and generates alerts when specific environmental thresholds are exceeded. The core of the project involves fetching environmental data, parsing the JSON response, evaluating key parameters, and generating automated alerts in case of abnormal conditions.
## Dependencies
The Integrated Environmental Monitoring System requires the following dependencies:

### 1. libcurl
Purpose: Used to send HTTP requests to fetch weather data from the API.

Installation: [libcurl](https://curl.se/libcurl/)

### 2. cJSON
Purpose: A lightweight library to parse and manipulate JSON data.

Installation: [cJSON](https://github.com/DaveGamble/cJSON)

## Project Flow

* ### Data Retrieval (API Call):

  The system communicates with an external weather API to fetch real-time environmental data.

  Below is the demonstration of how it is being used in this program via script file.
  
  ```bash
  json_data=$(curl "http://api.weatherapi.com/v1/current.json?key=d8170b5ec9f84e669bf123724240311&q=karachi")
  

* ### Data Parsing (cJSON):

  The fetched data is in JSON format, and it is parsed using the cJSON library to extract specific environmental metrics.

  Below is the code snippet of how it is being used in this program.

   ```c
    // Create a JSON object for storing weather data
    cJSON *data_object = cJSON_CreateObject();
    
    // Add date and weather information to the JSON object
    cJSON_AddStringToObject(data_object, "date", "2024-11-22 14:30:00");
    cJSON_AddNumberToObject(data_object, "temperature", 28.5);
    cJSON_AddNumberToObject(data_object, "humidity", 65);
    
    // Extract and store location details
    cJSON *location = cJSON_CreateObject();
    cJSON_AddStringToObject(location, "city", "Karachi");
    cJSON_AddStringToObject(location, "country", "Pakistan");
    cJSON_AddItemToObject(data_object, "location", location);
    
    // Write the JSON object to a file
    char *json_string = cJSON_Print(data_object);
    FILE *file = fopen("weather_data.json", "w");
    fprintf(file, "%s\n", json_string);
    fclose(file);
    
    // Clean up
    cJSON_Delete(data_object);
    free(json_string);
    ```


* ### Alert Generation:

  The system processes the parsed data to check if any environmental parameter exceeds predefined thresholds (e.g., temperature too high, air quality too low) and triggers real-time alerts.


* ### Data Storage:

  The data is stored locally in text files for further processing or historical reference.


* ### Automation (Shell Scripts):

  Automation scripts are used to regularly fetch data and process it without manual intervention.


## Future Enhancements

* Web Interface: Implementing a web interface for real-time monitoring and alerting.
  
* Data Visualization: Creating graphs or dashboards to visualize historical data and trends.

## Contributors

* Mohtashim Khan (CS-23050)
* Fahad Naeem (CS-23055)
* Asad Arif (CS-23088)



