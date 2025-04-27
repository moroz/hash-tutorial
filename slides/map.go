package main

import "fmt"

func main() {
	myMap := map[string]int{
		"foo": 42,
		"bar": 69,
		"baz": 420,
	}
	fmt.Printf("%#v\n", myMap)
}
