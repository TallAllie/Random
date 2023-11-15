#include <algorithm>  // generate_n
#include <iomanip>
#include <iostream>
#include <iterator>   // back_inserter
#include <random>
#include <string>
#include <boost/program_options.hpp>
using namespace boost::program_options;

// I'm using a cool gcc-specific feature called "Case Ranges".
//   https://gcc.gnu.org/onlinedocs/gcc/Case-Ranges.html

int main(int argc, char* argv[]) {
  std::random_device          r;
  std::default_random_engine  rng(r());
  std::uint32_t  count;
  std::uint64_t  width; // done as 64-bit for sizing values below
  bool           str;
  bool           sign;

  options_description desc("Allowed options");
  desc.add_options()("help,h", "print this help message")(
      "count,c", value<uint32_t>(&count)->default_value(1),
        "number of random numbers/strings to print")(
      "width,w", value<uint64_t>(&width)->default_value(32),
        "width in bits of each number length")(
      "string,s", bool_switch(&str)->default_value(false),
        "Generate strings if this switch is present.")(
      "signed,g", bool_switch(&sign)->default_value(false),
        "Generate SIGNED numbers if this switch is present.");

  variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    exit(1);
  }

  if (str == false) {
    if (sign == false) {
      switch (width) {
        case 64: {
          std::uniform_int_distribution<std::uint64_t> d(0);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << "0x" << std::hex << std::setfill('0')
                      << std::setw(width / 4) << d(rng) << "\n";
          }
          break;
        }
        case 33 ... 63: {
          const std::uint64_t  max = (1ULL << width) - 1ULL;
          std::uniform_int_distribution<std::uint64_t> d(0, max);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << "0x" << std::hex << std::setfill('0')
                      << std::setw(width / 4) << d(rng) << "\n";
          }
          break;
        }
        case 32: {
          std::uniform_int_distribution<std::uint32_t> d(0);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << "0x" << std::hex << std::setfill('0')
                      << std::setw(width / 4) << d(rng) << "\n";
          }
          break;
        }
        case 17 ... 31: {
          const std::uint32_t  max = (1 << width) - 1;
          std::uniform_int_distribution<std::uint32_t> d(0, max);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << "0x" << std::hex << std::setfill('0')
                      << std::setw(width / 4) << d(rng) << "\n";
          }
          break;
        }
        case 16: {
          std::uniform_int_distribution<std::uint16_t> d(0);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << "0x" << std::hex << std::setfill('0')
                      << std::setw(width / 4) << d(rng) << "\n";
          }
          break;
        }
        case 9 ... 15: {
          const std::uint16_t  max = (1 << width) - 1;
          std::uniform_int_distribution<std::uint16_t> d(0, max);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << "0x" << std::hex << std::setfill('0')
                      << std::setw(width / 4) << d(rng) << "\n";
          }
          break;
        }
        case 8: {
          std::uniform_int_distribution<std::uint8_t> d(0);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << "0x" << std::hex << std::setfill('0')
                      << std::setw(width / 4) << +d(rng) << "\n";
          }
          break;
        }
        case 1 ... 7: {
          const std::uint8_t  max = (1 << width) - 1;
          std::uniform_int_distribution<std::uint8_t> d(0, max);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << "0x" << std::hex << std::setfill('0')
                      << std::setw(width / 4) << +d(rng) << "\n";
          }
          break;
        }
        default: {
          std::cout << "I don't know what to do with a width: " << width << "\n";
          exit(1);
        }
      }
    } else {
      switch (width) {
        case 64: {
          std::uniform_int_distribution<std::int64_t>
              d(std::numeric_limits<std::int64_t>::min());
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << std::dec << d(rng) << "\n";
          }
          break;
        }
        case 33 ... 63: {
          const std::int64_t max = (1LL << (width-1LL)) - 1LL;
          const std::int64_t min = 0LL - (1LL << (width-1LL));
std::cout << "width=" << width << ", min=" << min << ", max=" << max << "\n";
          std::uniform_int_distribution<std::int64_t> d(min, max);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << std::dec << d(rng) << "\n";
          }
          break;
        }
        case 32: {
          std::uniform_int_distribution<std::int32_t>
              d(std::numeric_limits<std::int32_t>::min());
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << std::dec << d(rng) << "\n";
          }
          break;
        }
        case 17 ... 31: {
          const std::int32_t max = (1 << (width-1)) - 1;
          const std::int32_t min = 0 - (1 << (width-1));
          std::uniform_int_distribution<std::int32_t> d(min, max);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << std::dec << d(rng) << "\n";
          }
          break;
        }
        case 16: {
          std::uniform_int_distribution<std::int16_t>
              d(std::numeric_limits<std::int16_t>::min());
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << std::dec << d(rng) << "\n";
          }
          break;
        }
        case 9 ... 15: {
          const std::int16_t max = (1 << (width-1)) - 1;
          const std::int16_t min = 0 - (1 << (width-1));
          std::uniform_int_distribution<std::int16_t> d(min, max);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << std::dec << d(rng) << "\n";
          }
          break;
        }
        case 8: {
          std::uniform_int_distribution<std::int8_t>
              d(std::numeric_limits<std::int8_t>::min());
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << std::dec << +d(rng) << "\n";
          }
          break;
        }
        case 2 ... 7: {
          const std::int8_t max = (1 << (width-1)) - 1;
          const std::int8_t min = 0 - (1 << (width-1));
          std::uniform_int_distribution<std::int8_t> d(min, max);
          for (std::size_t ii = 0; ii < count; ++ii) {
            std::cout << std::dec << +d(rng) << "\n";
          }
          break;
        }
        case 1: {
          std::uniform_int_distribution<std::int8_t> d(0, 1);
          for (std::size_t ii = 0; ii < count; ++ii) {
            if (d(rng)) {
              std::cout << "true\n";
            } else {
              std::cout << "false\n";
            }
          }
          break;
        }
        default: {
          std::cout << "I don't know what to do with a width: " << width << "\n";
          exit(1);
        }
      }
    }
  } else { // string
    for (std::size_t ii = 0; ii < count; ++ii) {
      std::string s;
      s.clear();
      s.reserve(width);
      std::generate_n(std::back_inserter(s), width, [&rng]()->
        std::uint8_t {
          std::uniform_int_distribution<std::uint8_t> rand_char(0, UINT8_MAX);
          std::uint8_t c;
          while (!std::isprint(c = rand_char(rng)))
            ;
          return c;
        });
      std::cout << s << "\n";
    }
  }

  exit(0);
}  // main
