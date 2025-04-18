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
