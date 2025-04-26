In this video I'm going to show you how to implement a hash table in C from scratch.
I'm going to cover inserting, reading, resizing, deleting, and handling collisions, using a technique called "open addressing".
My name is Karol Moroz, and you are watching Make Programming Fun Again.

A hash table is a data structure that maps keys to values. The main advantage of hash tables is that, for large sets of data, they are BLAZINGLY FAST.
In fact, the average lookup time for a hash table is almost constant, regardless if you have 10 or 10000 keys.

You have most likely already used a hash table in a high level programming language:
In Go and Elixir, they are called maps, in Python -- dictionaries, in Ruby -- hashes, and in JavaScript -- objects.

The hash map implementation presented in this video is inspired by Chapter 20 of the book "Crafting Interpreters" by Robert Nystrom.
This book is available free of charge at craftinginterpreters.com.

The hash table we are going to build is going to use string keys and will only store integers, but with some creativity, you can modify the table to store any type of values.
The source code for the implementation is available on my Github and I'll put a link to the repository in the video description.



[Slide 0]
Now, before we dive into the code, let me quickly explain the overarching principles behind hash tables.
In its essence, a hash table is just a dynamic array, and in this array, some elements contain keys and values.
The elements of this array are called "buckets".

[Slide 1]
The reason a hash table can provide fast lookup and insertion times is due to the way entries are stored in the table.
Each entry is stored at a specific index, and we can very quickly calculate this index from a key using a hash function.
A hash function converts the key to a big number. Then we reduce this number modulo the size of the array, and we get the index where the element belongs in the array.
This way, we get much faster lookup times than with alternative approaches, such as binary search.
The hash function we are going to use is called FNV-1a.

[Slide 2]
It may happen that two or more keys in the table end up pointing to the same index. This is called a "key collision".
In this video, we are going to handle collisions using a technique called "open addressing".
The way this works is simple: if the index calculated by our hash function is already taken by a different entry, we check the next bucket, until we find one that is empty.

I am recording this video on an M4 Mac Mini running macOS Sequoia 15.4, using Clang 17. I will also make sure it compiles on Debian.
If you only have a Windows machine, you can install the Windows Subsystem for Linux and get a decent development environment this way.

In an empty directory, create two files: table.h and table.c, and open table.h in a code editor.
Start by adding an include guard. We're going to need to include stdint.h to use type aliases for integer types.
