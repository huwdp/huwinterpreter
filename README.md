


# HuwInterpreter
> HuwInterpreter is a hand written interpreter designed to parse and execute HuwCode script.

HuwInterpreter is an interpreter built in C++ for a custom language I developed named HuwCode. The project was built out of self-interest and understanding on how interpreters work and written. The language supports 70+ built in functions, custom user defined functions, scopes (each function has a scope), variables with types of double (number), string (text) and associated array.

User documentation can be found in the documentation folder [here](https://github.com/huwdp/huwinterpreter-mirror/tree/master/documentation).

WASM version can be found here (https://huwdp.co.uk/huwcode-wasm/output.html). Press Cancel button to see result after executing code.

![](https://huwdp.co.uk/sites/default/files/inline-images/huwinterpreter-in-action_0.png)
## Code Example
```
function fac(n)
{
    return facRec(1, n);
}

function facRec(acc, n)
{
    if (n < 2)
    {
        return acc;
    }
    return facRec(n * acc, n - 1);
}
print(fac(14));
```

## Dependencies

 - libcurl4-openssl-dev 
 - libcurl4
 - libreadline
 - libreadline-dev

## Installation

#### Building
```
sudo apt-get install git g++ cmake make libcurl4-openssl-dev curl pkg-config
sudo apt-get install lib32readline7 lib32readline-dev libreadline-dev
git clone https://github.com/huwdp/huwinterpreter.git
cd huwinterpreter/source
./build.sh
```
*Files will be put in source/build location.*


#### Install
Copy binary into sbin folder. *Binary is in build directory.*
```
sudo cp ./HuwInterpreter /usr/sbin/huw
```

#### Build App-Image
```
sudo apt-get install wget
cd huwinterpreter/build-appimage/
wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod a-x linuxdeployqt-continuous-x86_64.AppImage
chmod 777 linuxdeployqt-continuous-x86_64.AppImage
./build-app-image.sh
```

## Usage example
```
1. Usage: [filename] to run file.
2. Usage: -t [text] to run text.
3. Usage: --hc for HuwCode formatter
4. Usage: -h for help.
```
_For more examples and usage, please refer to the user documentation [here](https://github.com/huwdp/huwinterpreter-mirror/tree/master/documentation)._

### Releases
Binaries can be downloaded here (https://github.com/huwdp/huwinterpreter/releases).

Windows build available although some functionality is disabled. 
List of things disabled in Windows build:

- Readline user input
 - sleep
 - weekday
 - weekdayName
 - year
 - monthName
 - random
 - month
 - currentTime
 - clock
 - regexSearch
 - regexReplace
 - regexMatch
 - timeFormat
 - httpGet
 - httpPost
 - httpPut
 - httpDelete
 - now

## Meta
Huw Pritchard – [@huwdp](https://twitter.com/huwdp) – [huwdp.co.uk](https://huwdp.co.uk)
GNU GENERAL PUBLIC LICENSE Version 3 (GPL 3).. See [license.txt](https://github.com/huwdp/huwinterpreter-mirror/blob/master/license.txt) for more information.
## Contributing
1. Fork it [here](https://github.com/huwdp/huwinterpreter-mirror/fork)
2. Create your branch (`git checkout -b xxx`)
3. Commit your changes (`git commit -am 'Comment'`)
4. Push branch (`git push origin xxx`)
5. Create a new pull request
