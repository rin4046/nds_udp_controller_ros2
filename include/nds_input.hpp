#pragma once

#include <cstdint>

struct NDSInput {
  bool A = false;
  bool B = false;
  bool SELECT = false;
  bool START = false;
  bool RIGHT = false;
  bool LEFT = false;
  bool UP = false;
  bool DOWN = false;
  bool R = false;
  bool L = false;
  bool X = false;
  bool Y = false;
  bool TOUCH = false;
  bool LID = false;

  NDSInput() = default;

  void operator=(uint16_t keys) {
    A = keys & (1 << 0);
    B = keys & (1 << 1);
    SELECT = keys & (1 << 2);
    START = keys & (1 << 3);
    RIGHT = keys & (1 << 4);
    LEFT = keys & (1 << 5);
    UP = keys & (1 << 6);
    DOWN = keys & (1 << 7);
    R = keys & (1 << 8);
    L = keys & (1 << 9);
    X = keys & (1 << 10);
    Y = keys & (1 << 11);
    TOUCH = keys & (1 << 12);
    LID = keys & (1 << 13);
  }
};
