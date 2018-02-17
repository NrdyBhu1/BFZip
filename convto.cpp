#include <bitset>
#include <fstream>
#include <iterator>
#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <cmath>

using raw = std::array<uint8_t, 3>;
using to = std::array<uint8_t, 8>;

const std::map<char, uint8_t> convTo = {
  { '>', 0 },
  { '<', 1 },
  { '+', 2 },
  { '-', 3 },
  { '[', 4 },
  { ']', 5 },
  { '.', 6 },
  { ',', 7 }
};

raw from3bits(const to& from)
{
  raw buf;
  buf[0] = (from[0] << 5) | (from[1] << 2) | (from[2] >> 1);
  buf[1] = (from[2] << 7) | (from[3] << 4) | (from[4] << 1) | (from[5] >> 2);
  buf[2] = (from[5] << 6) | (from[6] << 3) | from[7];
  return buf;
}

void padTo8(std::vector<uint8_t>& vec) {
  int j = vec.size() % 8;
  if (j == 0) return;
  for (int i = 0; i < (8-j); ++i) vec.push_back(0);
}

std::vector<to> groupTo(const std::vector<uint8_t>& vec) {
  std::vector<to> buf;
  buf.reserve(vec.size()/8);
  for (int i = 8; i <= vec.size(); i += 8) {
    buf.push_back(to { vec[i-8], vec[i-7], vec[i-6], vec[i-5], vec[i-4], vec[i-3], vec[i-2], vec[i-1] });
  }
  return buf;
}

std::vector<raw> toToRaw(const std::vector<to>& vec) {
  std::vector<raw> buf;
  buf.reserve(vec.size());
  for (const to& it : vec) buf.push_back(from3bits(it));
  return buf;
}

std::vector<uint8_t> flattenRaw(const std::vector<raw>& vec) {
  std::vector<uint8_t> buf;
  buf.reserve(vec.size()*3);
  for (const raw& it : vec) {
    for (uint8_t rw : it) buf.push_back(rw);
  }
  return buf;
}

int main(int argc, char* argv[])
{
  std::vector<uint8_t> cmds;
  char buf;
  while (std::cin.get(buf)) {
    auto pair = convTo.find(buf);
    if (pair != convTo.end())
      cmds.push_back(pair->second);
  }
  int len = (int)std::ceil(((double)cmds.size()*3)/8);
  padTo8(cmds);
  std::vector<to> toCompress = groupTo(cmds);
  std::vector<uint8_t> almost = flattenRaw(toToRaw(toCompress));
  for (int i = almost.size(); i > len; --i) almost.pop_back();
  std::cout.write((char*)almost.data(), almost.size());
  return 0;
}
