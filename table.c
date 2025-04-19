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

static uint32_t hashString(const char *chars, const size_t length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash = (hash ^ (uint8_t) chars[i]) * 16777619;
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

static bool compareKey(const String *a, const String *b) {
  return a->length == b->length && a->hash == b->hash;
}

static Entry *findEntry(Entry *entries, const int capacity, const String *key) {
  // Begin looking for an index from key hash % capacity
  // since capacity will always be a power of 2, hash % capacity == hash & (capacity - 1)
  uint32_t index = key->hash & (capacity - 1);
  for (;;) {
    Entry *entry = &entries[index];
    if (entry->key == NULL || compareKey(entry->key, key)) {
      return entry;
    }

    index = (index + 1) & (capacity - 1);
  }
}

static void resizeTable(Table *table, const int newCapacity) {
  // Allocate new array of buckets
  Entry *entries = malloc(newCapacity * sizeof(Entry));

  // Set all keys and values to initial values
  for (int i = 0; i < newCapacity; i++) {
    entries[i].key = NULL;
    entries[i].value = 0;
  }

  // Start counting existing entries from zero, as there may be tombstones
  table->count = 0;
  for (int i = 0; i < table->capacity; i++) {
    const Entry *entry = &table->entries[i];
    if (entry->key == NULL) {
      continue;
    }

    // Re-insert all existing entries
    Entry *dest = findEntry(entries, newCapacity, entry->key);
    dest->key = entry->key;
    dest->value = entry->value;
    table->count++;
  }

  free(table->entries);
  table->entries = entries;
  table->capacity = newCapacity;
}

bool tableSet(Table *table, String *key, const int value) {
  if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
    const int newCapacity = table->capacity < 8 ? 8 : table->capacity * 2;
    resizeTable(table, newCapacity);
  }

  Entry *entry = findEntry(table->entries, table->capacity, key);
  const bool isNewKey = entry->key == NULL;
  if (isNewKey) {
    table->count++;
  }

  entry->key = key;
  entry->value = value;
  return isNewKey;
}

bool tableGet(const Table *table, const String *key, int *value) {
  if (table->count == 0) return false;

  const Entry *entry = findEntry(table->entries, table->capacity, key);
  if (entry->key == NULL) {
    return false;
  }

  *value = entry->value;
  return true;
}
