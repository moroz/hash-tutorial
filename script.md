In this video I'm going to show you how to build a hash table in C.
A hash table is an extremely useful data structure that lets you map any type of keys to any type of values.
You have most likely already used a hash table in a high level programming language:
In Go and Elixir, they are called maps, in Python -- dictionaries, in Ruby -- hashes, and in JavaScript -- objects.
In its essence, a hash table is just a dynamically growing array.
The "hash" in the name comes from hash functions, which are used to determine where exactly in this array to

Whenever you insert or look up a value in a hash table, you need to first calculate the 
