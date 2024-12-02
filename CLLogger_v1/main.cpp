#include "FileCache.cpp"
#include "Student.cpp"
#include <iostream>

using namespace std;
#define BUFFERSIZE 1024

int main() {
  FileCache filecache(BUFFERSIZE);
  filecache.open("jiashe.txt");
  filecache.write("xibaluoma");
  filecache.write("axiba");
  filecache.see_args();
  char *read = new char[BUFFERSIZE];
  filecache.read(read);
  cout << "what's read: " << read << endl;

  filecache.close();

  delete[] read;
  const char *ar = "asdfasdf";
  cout << ar << endl;

  //   FileCache cache("students.txt", 1024);
  //   cout << "the size of Student is: " << sizeof(Student) << endl;
  //   // 写入学生信息
  //   Student s1("Tom", "Male", 20);
  //   cache.write(0, (char *)&s1, sizeof(Student));

  //   Student s2("Lily", "Female", 18);
  //   cache.write(100, (char *)&s2, sizeof(Student));

  //   // 读取学生信息
  //   Student s3;
  //   cache.read(0, (char *)&s3, sizeof(Student));
  //   cout << "Name: " << s3.name << ", Gender: " << s3.gender
  //        << ", Age: " << s3.age << endl;

  //   Student s4;
  //   cache.read(100, (char *)&s4, sizeof(Student));
  //   cout << "Name: " << s4.name << ", Gender: " << s4.gender
  //        << ", Age: " << s4.age << endl;

  // 插入学生信息
  //   Student s5("John", "Male", 22);
  //   cache.insert(200, (char *)&s5, sizeof(Student));

  // 删除学生信息
  //   cache.remove(0, sizeof(Student));

  return 0;
}