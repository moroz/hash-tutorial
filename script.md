Greetings and welcome to Make Programming Fun Again! My name is Karol Moroz, and in this video I'm going to show you how to build a hash table in C.
A hash table is an extremely useful data structure that lets you map keys to values, and read them in almost constant time.
In fact, we could even say that hash tables are BLAZINGLY FAST.
You have most likely already used a hash table in a high level programming language:
In Go and Elixir, they are called maps, in Python -- dictionaries, in Ruby -- hashes, and in JavaScript -- objects.

In this video I'm going to cover inserting, reading, and deleting operations on a hash table.
The hash map implementation presented here is inspired by Chapter 20 of the book "Crafting Interpreters" by Robert Nystrom, in which a hash table is used to look up variables in the context of a bytecode virtual machine built in C.

[Slide 0]
Now, before we dive into the code, let me quickly explain the overarching principles behind hash tables.
In its essence, a hash table is just a dynamic array, and in this array, some elements contain keys and values.
The elements of this array are called "buckets".

[Slide 1]
The reason a hash table can provide fast lookup and insertion times is due to the way entries are stored in the table.
Each entry is stored at a specific index, and we can very quickly calculate this index using just the key using a hash function.
A hash function converts the key to a big number. Then we reduce this number modulo the size of the array, and we get the index where the element belongs in the array.
This way, we get much faster lookup times than with alternative approaches, such as binary search.

If the term "hash function" reminds you of functions such as MD5, SHA-256, or anything related to blockchains, you're actually correct.
All of these are "cryptographic hash functions". Theoretically, they could be used in hash tables. However, in practice, they are optimized for security, and they are too slow and complex for use in hash tables, so we're going to be using a much simpler and faster hash function called FNV-1a instead, which uses only XOR and 32-bit multiplication.

[Slide 2]
It may happen that two or more keys in the table end up pointing to the same index. This is called a "key collision".
There are many ways of dealing with this situation.
One way to handle collisions is to store all entries pointing to the same index in a linked list.
However, this approach is rather complex and does not work well with modern CPUs, because it requires following a lot of pointers.
In this video, we are going to use a technique called "open addressing" instead.
The way this works is quite simple: if the index calculated by our hash function is already taken by a different entry, we check the next bucket, until we find one that is empty.

Not all buckets in a hash table actually contain data, and we always want to keep some empty for future insertions.
The ratio of buckets containing entries to the table's capacity is called the "load factor".
In order to insert an entry 
Instead, a hash function is used to determine where a given key should be placed in the table.
The "hash" in the name comes from hash functions, which are used to determine where exactly in this array to

Whenever you insert or look up a value in a hash table, you need to first calculate the 
