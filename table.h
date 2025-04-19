#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  char *chars;
  size_t length;
  uint32_t hash;
} String;

typedef struct {
  String *key;
  int value;
} Entry;

typedef struct {
  int capacity;
  int count;
  Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(Table *table);
bool tableSet(Table *table, String *key, int value);
bool tableGet(Table *table, String *key, int *value);
bool tableDelete(Table *table, String *key);

String *copyString(const char *chars);

#endif
