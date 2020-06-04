# Import
import(string)
Loads file and executes script. Useful for creating external libraries and external code.
### Code examples
```
import("file.hco")
import("/home/user/file.hco")
import("../file.hco")
```
## Warning
HuwInterpreter loads in files relative from either where the binary file is located or the current directory the user is in within their Terminal. If your code is using an import function then change directory within Terminal to where the file executed will be and it should work. This problem might be fixed within the future if enough voices are heard.
