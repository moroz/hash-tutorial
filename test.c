#include "./table.h"
#include <criterion/criterion.h>
#include <stdio.h>

Test(Table, table_initialization) {
  Table table;
  initTable(&table);

  cr_assert_eq(table.capacity, 0);
  cr_assert_eq(table.count, 0);
  cr_assert_eq(table.entries, NULL);

  freeTable(&table);
}

Test(Table, copyString) {
  String *string = copyString("Hello, world!");
  cr_assert_eq(string->length, 13);
  cr_assert_eq(strcmp(string->chars, "Hello, world!"), 0);
}

Test(Table, tableSetGet) {
  Table table;
  initTable(&table);
  cr_assert_eq(table.count, 0);
  cr_assert_eq(table.capacity, 0);

  String *key = copyString("foo");

  int value = -1;
  bool actual = tableGet(&table, key, &value);
  cr_assert(!actual);
  cr_assert_eq(value, -1);

  actual = tableSet(&table, key, 42);
  cr_assert(actual);

  cr_assert_eq(table.count, 1);
  cr_assert_eq(table.capacity, 8);

  actual = tableGet(&table, key, &value);
  cr_assert(actual);
  cr_assert_eq(value, 42);

  freeTable(&table);
}

typedef struct {
  char *key;
  int value;
} HashEntry;

static const HashEntry ENTRIES[] = {{"foo", 42},           {"bar", 69},
                                    {"baz", 420},          {"bepis", 1337},
                                    {"power level", 9001}, {"stonks", -1000}};

static const int entryCount = sizeof(ENTRIES) / sizeof(HashEntry);

static void debugTable(Table *table) {
  printf("{\n");
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    if (entry->key == NULL) {
      printf("null,\n");
      continue;
    }

    printf("{key: \"%s\", \"value\": %d}\n", entry->key->chars, entry->value);
  }
  printf("}\n");
}

Test(Table, tableMultipleEntries) {
  Table table;
  initTable(&table);

  for (int i = 0; i < entryCount; i++) {
    String *key = copyString(ENTRIES[i].key);
    const bool isNewKey = tableSet(&table, key, ENTRIES[i].value);
    cr_assert(isNewKey);
  }

  debugTable(&table);

  String *new = copyString("not stonks");
  tableSet(&table, new, 1000);
  debugTable(&table);

  int value;
  String *key = copyString("foo");
  const bool exists = tableGet(&table, key, &value);
  cr_assert(exists);
  freeString(key);

  cr_assert_eq(value, 42);
}

Test(Table, hashStringCollisions) {
  for (int i = 0; i < entryCount; i++) {
    String *key = copyString(ENTRIES[i].key);
    printf("%s: %u, mod %d\n", key->chars, key->hash, key->hash & 7);
  }
}
