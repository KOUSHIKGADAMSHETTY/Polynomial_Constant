#include "cJSON.h"

cJSON *cJSON_CreateObject() {
  cJSON *item = (cJSON *)malloc(sizeof(cJSON));
  if (item) {
    memset(item, 0, sizeof(cJSON));
    item->type = 0;
  }
  return item;
}

cJSON *cJSON_Parse(const char *value) {
  cJSON *item = cJSON_CreateObject();
  item->value.valuestring = strdup(value);
  return item;
}

void cJSON_Delete(cJSON *c) {
  if (c) {
    free(c->string);
    free(c->value.valuestring);
    free(c);
  }
}

cJSON *cJSON_GetObjectItem(const cJSON *object, const char *string) {
  if (object && string) {
    return object->child;
  }
  return NULL;
}

int cJSON_IsObject(const cJSON *object) {
  return object && object->type == 0;
}

char *cJSON_Print(const cJSON *item) {
  return strdup(item->value.valuestring);
}
