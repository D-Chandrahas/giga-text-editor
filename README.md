## Build instructions for ubuntu
- `sudo apt update`
- `sudo apt-get install libncursesw5-dev`
- `sudo apt install pkg-config`
- `git clone https://github.com/D-Chandrahas/giga-text-editor`
- `cd giga-text-editor/src`
- `g++ -O3 *.cpp -o ../bin/giga.out $(pkg-config ncursesw --cflags --libs)`
- you can find the compiled binary in `giga-text-editor/bin`
