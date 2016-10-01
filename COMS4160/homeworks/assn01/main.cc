#include "prp.h"

int main(int ac, char **av) {
  POVRayParser parser;
  parser.parse(av[1]);
}
