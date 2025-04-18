#include "./table.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void initTable(Table *table) {
  table->capacity = 0;
  table->count = 0;
  table->entries = NULL;
}

void freeTable(Table *table) {
  free(table->entries);
  initTable(table);
}

static uint32_t hashString(const char *chars, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash = (hash ^ (uint8_t)chars[i]) * 16777619;
  }
  return hash;
}

String *copyString(const char *chars) {
  String *result = malloc(sizeof(String));
  result->chars = strdup(chars);
  result->length = strlen(chars);
  result->hash = hashString(chars, result->length);
  return result;
}
