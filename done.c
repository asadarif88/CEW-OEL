#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "startfun.h"
#include "endfunc.h"

// Function to read the JSON-like data from a file

int main() {
    const char *script_path = "bash script.sh"; // Replace with the actual script path

    // Activating the bash script for fetching data and stored in temporary file
    printf("Running the bash script: %s\n", script_path);
    run_bash_script(script_path);

    // Read the JSON data from the file
    char *file_content = read_file("temporaryfile.txt"); // Replace "data.txt" with your file name
    if (file_content == NULL) {
        fprintf(stderr, "Error: Could not read the file.\n");
        return 1;
    }


    // Clean the JSON string
    char *cleaned_json = clean_escaped_json(file_content);
    free(file_content); 
    if (cleaned_json == NULL) {
        fprintf(stderr, "Error: Could not clean the escaped JSON data.\n");
        return 1;
    }


    // Parse the cleaned JSON string
    cJSON *json = cJSON_Parse(cleaned_json);
    free(cleaned_json); // Free the cleaned JSON string
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "JSON Parse Error: %s\n", error_ptr);
        }
        return 1;
    }


    // Variables to store extracted data
    float temperature = 0.0;
    char humidity[10]; // Enough space to store humidity as a string

    // Extract data and store it in a JSON array

    extract_and_store_in_json_array(json, "weather_data_array.json", &temperature, humidity);

    printf("Current Temperature: %.2f C\n", temperature);
    printf("Current Humidity: %s\n ", humidity);

    // Clean up
    cJSON_Delete(json);

    return 0;
}

