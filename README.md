# LunaFileTransfer
I'm going to implement a file transfer through a websocket. The websocket is supported by Luna that is my open project.

## How to build
### step1. make dependency libraries
### step2. make Applications with Luna

## Build
## STEP1: How to build dependency libraries
### Linux & OS X
```bash
cd ~/LunaFileTransfer/dependency/Luna
git submodule init
git submodule update
mkdir build
cd build
cmake ..
make
```

## STEP2: How to build Applications with Luna
### Linux & OS X
```bash
cd ~/LunaFileTransfer
git submodule init
git submodule update
mkdir build  
cd build
cmake ..
make
```

## STEP3: How to test Applications
### Linux & OS X

### LunaFileTransferServer
```bash
cd ./LunaFileTransfer/build
./bin/LunaFileTransferServer
```
### LunaFileTransfer
For running LunaFileTransfer client, you have to input an IP where the LunaFileTransferServer is located and a file path.

```bash
cd ./LunaFileTransfer/build
./bin/LunaFileTransfer localhost ./LunaFileTransfer/README.md
```
