#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "startfun.h"

// Read file content
char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string

    fclose(file);
    return content;
}

// Function to clean escaped JSON string
char *clean_escaped_json(const char *escaped_json) {
    size_t len = strlen(escaped_json);
    char *cleaned_json = (char *)malloc(len + 1);
    if (cleaned_json == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (escaped_json[i] == '\\' && (escaped_json[i + 1] == '"' || escaped_json[i + 1] == '\\')) {
            // Skip the escape character
            continue;
        }
        cleaned_json[j++] = escaped_json[i];
    }
    cleaned_json[j] = '\0'; // Null-terminate the cleaned string

    return cleaned_json;
}

// Extract and store data in a JSON array
void extract_and_store_in_json_array(cJSON *json, const char *filename, float *temperature, char *humidity) {
    // Allocate dynamic memory for datetime
    char *datetime = (char *)malloc(20 * sizeof(char));
    if (datetime == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Create a new JSON object for the extracted data
    cJSON *data_object = cJSON_CreateObject();

    // Add current date and time to the data_object
    {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        snprintf(datetime, 20, "%04d-%02d-%02d %02d:%02d:%02d",
                 t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                 t->tm_hour, t->tm_min, t->tm_sec);
        cJSON_AddStringToObject(data_object, "date", datetime);
    }

    // Extract location details
    cJSON *location = cJSON_GetObjectItem(json, "location");
    if (location) {
        cJSON *location_object = cJSON_CreateObject();
        cJSON_AddItemToObject(data_object, "location", location_object);

        cJSON_AddStringToObject(location_object, "name", cJSON_GetStringValue(cJSON_GetObjectItem(location, "name")));
        cJSON_AddStringToObject(location_object, "region", cJSON_GetStringValue(cJSON_GetObjectItem(location, "region")));
        cJSON_AddStringToObject(location_object, "country", cJSON_GetStringValue(cJSON_GetObjectItem(location, "country")));
        cJSON_AddNumberToObject(location_object, "lat", cJSON_GetObjectItem(location, "lat")->valuedouble);
        cJSON_AddNumberToObject(location_object, "lon", cJSON_GetObjectItem(location, "lon")->valuedouble);
    }

    // Extract current weather details
    cJSON *current = cJSON_GetObjectItem(json, "current");
    if (current) {
        cJSON *current_object = cJSON_CreateObject();
        cJSON_AddItemToObject(data_object, "current_weather", current_object);

        cJSON_AddNumberToObject(current_object, "temperature_c", cJSON_GetObjectItem(current, "temp_c")->valuedouble);
        cJSON_AddNumberToObject(current_object, "humidity", cJSON_GetObjectItem(current, "humidity")->valueint);
        cJSON_AddStringToObject(current_object, "condition", cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(current, "condition"), "text")));

        // Store temperature and humidity into dynamically allocated variables
        *temperature = cJSON_GetObjectItem(current, "temp_c")->valuedouble;

        // Convert humidity to a string and store it
        int humidity_value = cJSON_GetObjectItem(current, "humidity")->valueint;
        sprintf(humidity, "%d", humidity_value);
    }

    // Read existing JSON array from the file, or create a new one if the file does not exist
    cJSON *json_array = NULL;
    FILE *file = fopen(filename, "r");
    if (file) {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        char *file_content = (char *)malloc(file_size + 1);
        if (file_content) {
            fread(file_content, 1, file_size, file);
            file_content[file_size] = '\0';
            json_array = cJSON_Parse(file_content);
            free(file_content);
        }
        fclose(file);
    }

    if (!json_array || !cJSON_IsArray(json_array)) {
        if (json_array) {
            cJSON_Delete(json_array);
        }
        json_array = cJSON_CreateArray();
    }

    // Append the new data object to the JSON array
    cJSON_AddItemToArray(json_array, data_object);

    // Write the updated JSON array back to the file
    char *json_string = cJSON_Print(json_array);
    file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s\n", json_string);
        fclose(file);
        
    } else {
        perror("Error opening file for writing");
    }

    // Clean up
    cJSON_Delete(json_array);
    free(json_string);
    free(datetime); // Free dynamic memory
}









