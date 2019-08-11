# JSON
HuwCode's internal structure does not support null values.

##  JSON Encode
JsonEncode returns JSON from a value.

### Code example

```
/* Empty array */
let emptyArray = array();
print(jsonEncode(emptyArray));

/* Array */
let list = array();
list[1] = "1";
list[2] = "2";
list[3] = "3";
list[4] = "4";
list[5] = "5";
print(jsonEncode(list));

/* Associated array */
let arrayOfArrays = array();
let innerArray = array();
innerArray["1"] = "1";
innerArray["2"] = "2";
arrayOfArrays["array"] = innerArray;
print(jsonEncode(arrayOfArrays));
```

## JSON Decode
JSON decode takes JSON and returns a HuwCode variable.

### Code example
```
/* One element array */
print(jsonDecode("[1]"));

/* Empty object */
print(jsonDecode("{}"));

/* Normal array */
print(jsonDecode("[1,2,3,4,5]"));

/* Associated array */
print(jsonDecode("{ \"key1\" : { \"key2\": \"value\"}"));
```
