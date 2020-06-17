
# HuwInterpreter
> HuwInterpreter is a hand written interpreter designed to parse and execute HuwCode script.

HuwInterpreter is an interpreter built in C++ for a custom language I developed named HuwCode. HuwCode was named by two people I know of, I did not name the scripting language myself. The project was built out of self-interest and understanding on how interpreters work and written.

The language supports 70 built in functions, custom user defined functions, scopes (each function has a scope), variables with types of doubles (number), strings (text) and hash tables. Hash tables allow any of types of variables making itself an associated array.

User documentation can be found in the documentation folder [here](https://github.com/huwdp/huwinterpreter-mirror/tree/master/documentation).

![](https://huwdp.co.uk/sites/default/files/inline-images/huwinterpreter-in-action_0.png)
## Code Example
```
function fac(n)
{
    return factailrec(1, n);
}

function factailrec(acc, n)
{
    if (n < 2)
    {
        return acc;
    }
    return factailrec(n * acc, n - 1);
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
sudo apt-get install git g++ qt5-qmake make libcurl4-openssl-dev curl lib32readline7 lib32readline-dev libreadline-dev
git clone https://github.com/huwdp/huwinterpreter.git
cd huwinterpreter/source
qmake CONFIG+=release HuwInterpreter.pro
make
```

#### Install
Copy binary into sbin folder.
```
sudo cp ./HuwInterpreter /usr/sbin/huw
```

#### Build App-Image
```
sudo apt-get install wget
cd huwinterpreter/deploy-appimage/
wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod a-x linuxdeployqt-continuous-x86_64.AppImage
chmod 777 linuxdeployqt-continuous-x86_64.AppImage
./build-app-image.sh
```

#### Problems
#### Ubuntu 16.04 cannot find qmake

##### Find qmake location
```
which qmake
```
##### Create folders
```
sudo mkdir /usr/lib/qt5/
sudo mkdir /usr/lib/qt5/bin
```
##### Copy qmake or create sym-link
```
sudo cp /usr/bin/qmake /usr/lib/qt5/bin/qmake
```
You may need to replace qmake location

## Usage example
```
1. Usage: [filename] to run file.
2. Usage: -t [text] to run text.
3. Usage: --hc for HuwCode formatter
4. Usage: -h for help.
```
_For more examples and usage, please refer to the user documentation [here](https://github.com/huwdp/huwinterpreter-mirror/tree/master/documentation)._

### Optional Software
- Qt Creator
- qmake
## Development setup
System is built under Qt Creator but can be compiled by just using make. Open HuwInterpreter.pro using Qt Creator and configure your own build settings via Qt Creator's GUI.
## Meta
Huw Pritchard – [@huwdp](https://twitter.com/huwdp) – [huwdp.co.uk](https://huwdp.co.uk)
GNU GENERAL PUBLIC LICENSE Version 3 (GPL 3).. See [license.txt](https://github.com/huwdp/huwinterpreter-mirror/blob/master/license.txt) for more information.
## Contributing
1. Fork it [here](https://github.com/huwdp/huwinterpreter-mirror/fork)
2. Create your branch (`git checkout -b xxx`)
3. Commit your changes (`git commit -am 'Comment'`)
4. Push branch (`git push origin xxx`)
5. Create a new pull request
