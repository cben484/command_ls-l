#include "FileCache.cpp"
#include <iostream>
#include <string>

using namespace std;
#define BUFFERSIZE 1024

int main(int argc, char *argv[]) {

  FileCache filecache(BUFFERSIZE);
  char *read = new char[BUFFERSIZE];
  string command;
  string data;
  int seek = -1;
  int mode = -1;

  // 此处不可重复打开，虽然不知道为什么，但是时间好像不允许去深究了
  filecache.open("jiashe.txt");

  while (true) {

    std::cout << "Command: ";
    std::cin >> command;

    if (command == "-1") {
      break;
    }

    if (command == "r") {
      std::cout << "The file is: ";
      filecache.read(read, 1024);
      cout << read << endl;
    }

    if (command == "w") {
      std::cout << "What's you want to write: ";
      std::cin >> data;
      filecache.write(data);
    }

    if (command == "lseek") {
      std::cout << "Where do you want to go: ";
      std::cin >> seek;
      std::cout << "What's The Mode (1,2 or 3 ) : ";
      std::cin >> mode;
      filecache.lseek(seek, mode);
      // std::cin.ignore();
    }

    cout << "what's the command: " << command << endl;
    cout << "what's the data: " << data << endl;
    cout << "what's the seek: " << seek << endl;
    cout << "what's the mode: " << mode << endl;
  }

  // filecache.write("xibaluoma");
  // filecache.write("axiba");
  filecache.see_args();

  filecache.close();

  delete[] read;

  return 0;
}