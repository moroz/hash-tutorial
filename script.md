In this video I'm going to show you how to implement a hash table in C from scratch.
I'm going to cover inserting, reading, resizing, deleting, and handling collisions.
My name is Karol Moroz, and you are watching Make Programming Fun Again.

A hash table is a data structure that maps keys to values.
You have most likely already used a hash table in a high level programming language:
In Go and Elixir, they are called maps, in Python -- dictionaries, in Ruby -- hashes, and in JavaScript -- objects.

The hash map implementation presented in this video is inspired by Chapter 20 of the book "Crafting Interpreters" by Robert Nystrom.
This book is available free of charge at craftinginterpreters.com.

The hash table we are going to build is going to use string keys and will only store integers, but with some creativity, you can modify the table to store any type of values.
The source code for the implementation is available on my Github and I'll put a link to the repository in the video description.

[Slide: Essence]
Now, before we dive into the code, let me quickly explain the overarching principles behind hash tables.
In its essence, a hash table is just a dynamic array, and in this array, some elements contain keys and values.
The elements of this array are called "buckets".

[Slide: Hash functions]
The reason a hash table can provide fast lookup and insertion times is due to the way entries are stored in the table.
Each entry is stored at a specific index, and we can very quickly calculate this index from a key using a hash function.
A hash function converts the key to a big number. Then we reduce this number modulo the size of the array, and we get the index where the element belongs in the array.
This way, we get much faster lookup times than with alternative approaches, such as binary search.
The hash function we are going to use is called FNV-1a.

[Slide: Collisions]
It may happen that two or more keys in the table end up pointing to the same index. This is called a "key collision".
In this video, we are going to handle collisions using a technique called "open addressing".
The way this works is simple: if the index calculated by our hash function is already taken by a different entry, we check the next bucket, and the next one, until we find one that is empty.

[Slide: Resizing]
Handling collisions is kind of a waste of time, and it slows down insertion and lookup times.
You can reduce the risk of collisions by giving your entries enough space to live and grow.
The ratio of the number of entries to the table's total capacity is called the table's load factor.
We need to make sure it never exceeds a reasonable limit, let's say, 75%.
If the table becomes too full, we allocate a new array that is two times larger than the previous one.
Then, we copy all elements from the old table to the new one, and finally we can free the old array.
Please note that most items will likely end up at new indices in this new array.

I am recording this video on an M4 Mac Mini running macOS Sequoia 15.4, using Clang 17.
The reason I'm doing this on a Mac is that it's actually a bit more difficult to set up and compile C projects on macOS than it is on Debian, and I wanted to show you the issues you may encounter when linking external libraries. However, I will also make sure that the project compiles on Debian-based operating systems.
If you are on Windows, you can set up a complete Linux-based environment using the Windows Subsystem for Linux, and then you can just follow all the steps for Linux.

In an empty directory, create two files: table.h and table.c, and open table.h in a code editor.
Start by adding an include guard. Then, include stdint.h so we can use type aliases for integer types.
Next, we are going to define our data types, starting with a string type.
In C, there is no built-in string type, and traditionally, text is stored in arrays of characters ending with a zero, also known as a null terminator.
Our String type is going to wrap this array, and it's also going to store its length and the computed hash value for this string.

The Entry struct is what we are going to store in the hash table. For the sake of simplicity, this implementation only supports string keys and integer values, but with some creativity, you can modify it to handle any type of values.
As a side note, in the Entry struct, you could also use a wider integer type for the value, like `int64_t`.
This is because on 64-bit systems, the compiler will pad this struct to be 16 bytes long anyway, so if you only use a 32-bit integer, you're kind of wasting space.

Finally, define the Table struct, representing the actual hash table.
This struct has three fields: `count` represents the number of buckets that are currently occupied; `capacity` is the total size of the array; and `entries` is a pointer to the actual array of buckets.

Then, we declare three functions.
initTable, which will function as a constructor. freeTable, which is responsible for cleaning up. growTable, which resizes an existing hash table.

Next, open the file table.c. Include the header file we have just written.
We are also going to need stddef.h for NULL, stdlib.h for malloc() and free(), and string.h for memset().

Now, let's implement initTable. This function is very simple, the only thing it does is set the fields of the Table struct to their zero values.
freeTable is even simpler: free() the array of entries, and call the constructor again, resetting the table to its default state.

growTable is a bit more involved: First, we allocate a new array for entries. Then, we need to initialize all elements in this array to zero values. We _could_ do this with a for loop, but since all of these are going to end up as zeros, anyway, we can use memset() to set all the bytes in the array to zero, which will have the same effect.
Then, we can free() the old array and point the struct's `entries` field to the new array. Then, we set the `capacity` to the size of the new array, and set `count` to 0.
Now, you may have noticed that this function does not really do what it's supposed to do: We haven't yet written any logic to copy the entries between the two arrays.
This is fine, because at this point we have no logic to set and read items, either, so the table is guaranteed to be empty.

Now that we have a barebones implementation, we can write some tests. I'm going to use a testing framework called Criterion, which has been recommended to be in the comment section.
On macOS, you can install Criterion using Homebrew. On Debian and derivatives, install the package `libcriterion-dev` using `apt`.

Create a new file called test.c and open it in your editor. Include Criterion's header file and the table.h file we have written.

If you are on macOS and have a setup similar to mine, at this point you are going to get LSP errors, because Clangd will not be able to find the header files for Criterion.
You can fix this by creating a file called `.clangd` in the project directory.
In this file, add these three lines, telling Clangd where to find header files for the Criterion framework.

Back in test.c, define a test example using Criterion's `Test` macro.
This macro takes two parameters: the name of a test suite, and the name of the test example. Let's call the test suite "Table" and the example "initResizeFree", because we are going to test the constructor, the `growTable` function, and the destructor.
In the test example, declare a Table and call `initTable` with a pointer to it.
Using the `cr_assert_eq` macro, assert that all fields in the struct are now set to zero values.

Next, let's write a Makefile.
On all platforms, we're going to need the linker flag `-lcriterion`. This tells the linker to link against the Criterion library.
Then, we're going to add some conditional logic.
Using `uname`, we check if we are building the program on macOS, and if that is the case, we add additional compiler and linker flags to help locate Criterion's header files and libraries.

Then, we define a target called `test`, which depends on two source files: table.c and test.c.
For this target, we use a bunch of magic variables and command-line flags:
CC stands for the C compiler binary, and this is ususally going to be either Clang or GCC.
CFLAGS are the resolved compiler flags.
-g compiles the binary with debug information.
$^ (dollar caret) is a special variable that expands to all prerequisites of a target, in this case it's going to be the two C files: table.c and test.c.
-o $@ (dash oh dollar at) is going to expand to -o test, meaning that the linked binary will be called "test".
Finally, LDFLAGS are the resolved linker flags.

After this command, we execute the compiled `test` binary. We mark the `test` target as a "phony target", which means Make will always build it and execute it, even if the underlying C files haven't changed.

In a new terminal, run `make test`, and if you have set everything correctly, you should get a pretty and colorful output telling you that your tests have passed.

Next, let's test resizing the table. In test.c, call `growTable` with a pointer to the table and the number 8. Using `cr_assert_eq`, test that `count` equals 0 and that `capacity` equals 8.
Now, using a different macro, `cr_assert_neq`, assert that `entries` does not equal `NULL`. Then, call `freeTable` with a pointer to the table, and you can copy and paste the assertions that we used for `initTable`.

If you `make test` in the other terminal, the tests should still be passing.
