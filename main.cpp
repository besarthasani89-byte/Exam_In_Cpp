#include "circular_buffer.h"

#include <cassert>
#include <sstream>
#include <iostream>
#include <string>

void test_write_read_order()
{
  CircularBuffer<int, 4> buf;
  buf.write(10);
  buf.write(20);
  buf.write(30);

  int value = 0;
  assert(buf.read(value) && value == 10);
  assert(buf.read(value) && value == 20);
  assert(buf.size() == 1);
  assert(!buf.full());
}

void test_overwrite_behavior()
{
  CircularBuffer<int, 4> buf;
  buf.write(1);
  buf.write(2);
  buf.write(3);
  buf.write(4);
  buf.write(5); // overwrites 1

  assert(buf.size() == 4);
  assert(buf.full());

  int value = 0;
  assert(buf.read(value) && value == 2);
  assert(buf.read(value) && value == 3);
  assert(buf.read(value) && value == 4);
  assert(buf.read(value) && value == 5);
  assert(!buf.read(value)); // empty now
}

void test_clear()
{
  CircularBuffer<int, 4> buf;
  for (int i = 0; i < 4; ++i)
  {
    buf.write(i);
  }
  buf.clear();
  int value = 0;
  assert(buf.size() == 0);
  assert(!buf.full());
  assert(!buf.read(value));
}

void test_stream_output()
{
  CircularBuffer<int, 4> buf;
  buf.write(7);
  buf.write(8);
  buf.write(9);

  std::stringstream ss;
  ss << buf;
  assert(ss.str() == "7 8 9");

  buf.write(10);
  buf.write(11); // overwrites 7

  std::stringstream ss2;
  ss2 << buf;
  assert(ss2.str() == "8 9 10 11");
}

int main()
{
  test_write_read_order();
  test_overwrite_behavior();
  test_clear();
  test_stream_output();
  std::cout << "All tests passed succesfully!\n";
  return 0;
}
