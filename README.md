# Yet Another Game of Life
## What is it?

This is just an implementation of good old Conway's Game of Life in C++ for WebAssembly and nothing else.


![alt text](https://github.com/muxamot/yal/blob/master/pic/screenshot_2.png "Screenshot 2")


## How to build

0) Install clang compiler, cmake and make to your system 
1) Install Emscripten framework to your system and make shure you have `emcmake` and `em++` commands working
2) Change your directory to `yal/build`
2) Configure project with `emcmake cmake .. -DCMAKE_BUILD_TYPE=Release`
3) Build project with `make -j4`
4) After succesful build there will be files `yal.wasm` (contains WebAssembly application code), 
`yal.js` (contains application runtime in JS) and `yal.html` (contains end-user web page to interact with) in `yal/build/bin`

## How to run
Unfortunately, protection from cross origin resource sharing (CORS) most likely will not allow you to run your the newely built
 Web Assembly application locally by just opening `yal.html` file in web browser. 
Therefore, you will need to install any http web server (for example Apache) on your system. For example, after installing Apache in Fedora,
 you need to copy the files from the `yal/build/bin` directory to `/var/www/html` and start the web server with the `systemctl start httpd` command. 
Than navigate to `http://localhost/yal.html` and enjoy tha game.
Check your OS distribution manuals to learn more.
 

Also you can just host this application on any web server you may whant to - it is fully client-side, no special 
support from server is required. 

## About
(c) 2023 - Mikhail A. Motylenok

This is free software, made just for fun.

## Build status
![build workflow](https://github.com/muxamot/yal/actions/workflows/cmake.yml/badge.svg)
