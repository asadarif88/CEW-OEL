#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "startfun.h"
#include "endfunc.h"
// Function to read the JSON-like data from a file

int main() {
    const char *script_path = "bash script.sh"; // Replace with the actual script path

    // Run the bash script
    run_bash_script(script_path);

    // Step 1: Read the escaped JSON data from the file
    char *file_content = read_file("temporaryfile.txt"); // Replace "data.txt" with your file name
    if (file_content == NULL) {
        return 1;
    }

    // Step 2: Clean the escaped JSON string
    char *cleaned_json = clean_escaped_json(file_content);
    free(file_content); // Free the original content
    if (cleaned_json == NULL) {
        return 1;
    }

    // Step 3: Parse the cleaned JSON string
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

    
    extract_and_store_in_json_array(json, "weather_data_array.json", &temperature, humidity);

    
    

    // Clean up
    cJSON_Delete(json);

    return 0;
}
