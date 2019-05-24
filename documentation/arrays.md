# Array functions

## Array
array()
Array function returns an array. Array function requires 0 arguments.

Associative Array is an abstact collection of key, value pairs. The internal implementation of the array within HuwCode is implemented with std::unordered_map.

## Get value in an array
An element can be access by the key in an array by using square brackets. E.g. array["element1"];.
```
let list = array();
list["item1"] = "Item 1";
print(list["item1"]);
```

## Set value in an array
An element can be set in an array by the key by using square brackets. E.g. array["element1"] = "Hello World!";
```
let list = array();
list["item1"] = "Item 1";
print(list);
```

## ArrayUnset
arrayUnset(array, key)
ArrayUnset function removes the value in the associative array by the key.

## Example
```
let i = 0;
let list = array();

/* Add items to the hash table */
while (i < 10)
{
    arraySet(list, i, "Item " + i);
    i++;
}

/* Print items */
let i = 0;
while (i < 10)
{
    print(arrayGet(list, i));
    i++;
}

print("Array count: " + count(list));
```
