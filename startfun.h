#include "cJSON.h"
#include<time.h>

#ifndef startfunc_h
#define startfunc_h

char *read_file(const char *filename);
char *clean_escaped_json(const char *escaped_json);
void extract_and_store_in_json_array(cJSON *json, const char *filename, float *temperature, char *humidity);
#endif