#include "./table.h"
#include <criterion/criterion.h>

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
