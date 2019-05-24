# Regex functions

## Regex search
regexSearch(text, regex)
Regex search function returns true if the regular expression has at least one match, the function returns false otherwise.
### Code example
```
regexSearch("Roses are #ff0000", "#([a-f0-9]{2})"); /*  Returns true */
```

## Regex replace
regexReplace(text, regex, )
Regex replace function matches and replaces any matched text with the regex substitution.
### Code example
```
regexReplace("Quick brown fox", "a|e|i|o|u", "[$&]"); /* Returns "Q[u][i]ck br[o]wn f[o]x" */
```

## Regex match
regexMatch(text, regex)
Regex search function returns an associative array (Hash Table) with all regular expression matches.
### Code example
```
let result = regexMatch("huwcode.hco", "[a-z]+\\.hco");
print(result);
```
