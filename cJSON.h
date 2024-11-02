#ifndef cJSON_H
#define cJSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cJSON {
  struct cJSON *next, *prev;
  struct cJSON *child;
  char *string;
  int type;
  union {
    double valuedouble;
    int valueint;
    char *valuestring;
  } value;
} cJSON;

cJSON *cJSON_Parse(const char *value);
void cJSON_Delete(cJSON *c);
cJSON *cJSON_GetObjectItem(const cJSON *object, const char *string);
int cJSON_IsObject(const cJSON *object);
char *cJSON_Print(const cJSON *item);

#endif // cJSON_H
