#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class FileCache {
private:
  string filename;     // 文件名
  char *buffer = NULL; // 缓存区
  int bufferSize;      // 缓存大小
  int fileLength;      // 文件长度
  int currentPos;      // 当前文件读写位置
  int isModified;      // 缓存是否被修改
  fstream file;        // 文件流

  void init() {
    buffer = new char[bufferSize];
    memset(buffer, 0, bufferSize);
    currentPos = 0;
    isModified = 0;
  }

  int getFileLength() {
    file.seekg(0, ios::end);
    return file.tellg();
  }

public:
  void see_args() {
    cout << "the filename is: " << filename << endl;
    if (buffer)
      cout << "the buffer is: " << buffer << endl;
    cout << "the bufferSize is: " << bufferSize << endl;
    cout << "the fileLength is: " << fileLength << endl;
    cout << "the currentPos is: " << currentPos << endl;
    cout << "the isModified is: " << isModified << endl;
  }

  FileCache(int buffersize) : bufferSize(buffersize) { init(); }
  FileCache() {}

  int open(string thefilename) {
    filename.assign(thefilename);
    file.open(filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
      file.open(filename, ios::out | ios::binary);
    }
    fileLength = getFileLength();
    return EXIT_SUCCESS;
  }

  void read(char *read_data) { memcpy(read_data, buffer, currentPos); }

  int write(const char *write_data) {
    if (currentPos + strlen(write_data) >= bufferSize) {
      cerr << "The Buffer is overflowingggggggg" << endl;
      return EXIT_FAILURE;
    }
    memcpy(buffer + currentPos, write_data, strlen(write_data));
    currentPos += strlen(write_data);
    file << write_data;
    isModified++;
    return EXIT_SUCCESS;
  }

  void lseek() {}

  void close() {
    file.close();
    delete[] buffer;
  }
};