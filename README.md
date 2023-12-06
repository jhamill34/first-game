# First Game

> I have no idea what I'm doing. 

Trying to learn some C++ and some Graphics programming froms scratch. 

## Setup 

```bash 
git clone https://github.com/jhamill34/first-game.git
cd first-game
git submodule update --init --recursive # leave out --init on updates

# OR
git clone --recurse-submodules https://github.com/jhamill34/first-game.git
```

## Build and run 

Just your typical CMake routine after cloning this onto your machine. I'm developing on 
macos with an M1 chip. 

```bash
mkdir build 
cd build 
cmake ..
make 
./apps/firstGame/FirstGameApp
```



