// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "../JsonBuffer.hpp"

namespace ArduinoJson {
namespace Internals {

// A node for a singly-linked list.
// Used by List<T> and its iterators.
template <typename T>
class ListNode {
  friend class ArduinoJson::JsonBuffer;

 public:
  ListNode<T>* next;
  T content;

 private:
  void init(JsonBuffer*) { next = NULL; }
};
}
}
