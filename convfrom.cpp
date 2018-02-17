#include <fstream>
#include <iterator>
#include <iostream>
#include <array>
#include <vector>

using raw = std::array<uint8_t, 3>;
using to = std::array<uint8_t, 8>;

constexpr std::array<char, 8> convFrom{
 '>', '<', '+', '-', '[', ']', '.', ','
};

to to3bits(raw from)
{
  to buf;
  buf[0] = from[0] >> 5;
  buf[1] = (from[0] & 0b00011100) >> 2;
  buf[2] = ((from[0] & 0b11) << 1) | (from[1] >> 7);
  buf[3] = (from[1] & 0b01110000) >> 4;
  buf[4] = (from[1] & 0b00001110) >> 1;
  buf[5] = ((from[1] & 0b1) << 2) | (from[2] >> 6);
  buf[6] = (from[2] & 0b00111000) >> 3;
  buf[7] = from[2] & 0b111;
  return buf;
}

void padTo3(std::vector<uint8_t>& vec) {
  int j = vec.size() % 3;
  if (j == 0) return;
  for (int i = 0; i < (3-j); ++i) vec.push_back(0);
}

std::vector<raw> groupRaw(const std::vector<uint8_t>& vec) {
  std::vector<raw> buf;
  buf.reserve(vec.size()/3);
  for (int i = 3; i <= vec.size(); i += 3)
    buf.push_back(raw { vec[i-3], vec[i-2], vec[i-1] });
  return buf;
}

std::vector<to> rawToTo(const std::vector<raw>& vec) {
  std::vector<to> buf;
  buf.reserve(vec.size());
  for (const raw& it : vec) buf.push_back(to3bits(it));
  return buf;
}

std::vector<uint8_t> flattenTo(const std::vector<to>& vec) {
  std::vector<uint8_t> buf;
  buf.reserve(vec.size()*8);
  for (const to& it : vec) {
    for (uint8_t n : it) buf.push_back(n);
  }
  return buf;
}

int main(int argc, char* argv[])
{
  std::istream_iterator<uint8_t> begin(std::cin), end;
  std::vector<uint8_t> bytes(begin, end);
  padTo3(bytes);
  std::vector<uint8_t> decode = flattenTo(rawToTo(groupRaw(bytes)));
  for (uint8_t i : decode) std::cout.put(convFrom[i]);
  return 0;
}
