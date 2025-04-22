Greetings and welcome to Make Programming Fun Again! My name is Karol Moroz, and in this video I'm going to show you how to build a hash table in C.
A hash table is an extremely useful data structure that lets you map keys to values.
You have most likely already used a hash table in a high level programming language:
In Go and Elixir, they are called maps, in Python -- dictionaries, in Ruby -- hashes, and in JavaScript -- objects.

Before we jump into the code editor, let me first give you a brief overview of the hash table's design.
In its essence, a hash table is just a dynamic array, and each element of this array stores a key and a value.
The elements of this array are called "buckets".

The reason a hash table can provide fast lookup and insertion times is due to the way entries are stored in the table.
Each entry is stored at a specific index in this array of buckets, and the actual index is calculated based on the entry's key using a hash function.
A hash function converts a key of arbitrary length to a number. When you reduce this number modulo the size of the array, you get the index of the bucket.
When you insert 
Not all buckets in a hash table actually contain data, and we always want to keep some empty for future insertions.
The ratio of buckets containing entries to the table's capacity is called the "load factor".
In order to insert an entry 
Instead, a hash function is used to determine where a given key should be placed in the table.
The "hash" in the name comes from hash functions, which are used to determine where exactly in this array to

Whenever you insert or look up a value in a hash table, you need to first calculate the 
