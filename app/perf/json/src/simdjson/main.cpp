#include <iostream>
#include "lib/simdjson.h"

using namespace std;

struct coordinate_t {
  double x;
  double y;
  double z;

  auto operator<=>(const coordinate_t &) const = default;

  // To print a coordinate result using ostream.
  //
  // friend ostream &operator<<(ostream &out, const coordinate_t &point) {
  //   out << "coordinate_t {x: " << point.x << ", y: " << point.y
  //       << ", z: " << point.z << "}";
  //   return out;
  // }
};

using namespace simdjson;

class on_demand {
public:
  bool parse(const padded_string &json);
  coordinate_t result{};
  size_t count{};

private:
  ondemand::parser parser{};
};

bool on_demand::parse(const padded_string &json) {
  count = 0;
  auto doc = parser.iterate(json);
  for (ondemand::object point_object : doc["coordinates"]) {
    result.x += double(point_object["x"]);
    result.y += double(point_object["y"]);
    result.z += double(point_object["z"]);
    count++;
  }
  return true;
}

coordinate_t run(const padded_string &json) {
  on_demand reader;
  reader.parse(json);
  reader.result.x /= reader.count;
  reader.result.y /= reader.count;
  reader.result.z /= reader.count;
  return reader.result;
}

bool verify(coordinate_t result) {
  if (result.x >= -4.99e-30 || result.x <= -5.01e-30)
    return false;
	if (result.y <= 4.99e+30 || result.y >= 5.01e+30)
    return false;
	if (result.z <= 0.499 || result.z >= 0.501)
    return false;

  return true;
}

int main() {
  padded_string text;
  const auto &error = padded_string::load("exe/perf.json").get(text);
  if (error) {
    cerr << "could not load file" << endl;
    return EXIT_FAILURE;
  }

  auto result = run(text);
  // cout << result << endl;
}
