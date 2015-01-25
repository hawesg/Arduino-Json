// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "../JsonBuffer.hpp"
#include "ListConstIterator.hpp"
#include "ListIterator.hpp"

namespace ArduinoJson {
namespace Internals {

// A singly linked list of T.
// The linked list is composed of ListNode<T>.
// It is derived by JsonArray and JsonObject
template <typename T>
class List {
  friend class ArduinoJson::JsonBuffer;

 public:
  typedef T value_type;
  typedef ListNode<T> node_type;
  typedef ListIterator<T> iterator;
  typedef ListConstIterator<T> const_iterator;

  // Returns true if the object is valid
  // Would return false in the following situation:
  // - the memory allocation failed (StaticJsonBuffer was too small)
  // - the JSON parsing failed
  bool success() const { return _buffer != NULL; }

  // Returns the numbers of elements in the list.
  // For a JsonObject, it would return the number of key-value pairs
  int size() const;

  iterator begin() { return iterator(_firstNode); }
  iterator end() { return iterator(NULL); }

  const_iterator begin() const { return const_iterator(_firstNode); }
  const_iterator end() const { return const_iterator(NULL); }

 protected:
  // Construction it must be done via JsonBuffer.
  // Only "invalid" instances are created with this contstructor.
  List() : _buffer(NULL) {}

  // Creates an empty List<T> attached to a JsonBuffer.
  // The JsonBuffer allows to allocate new nodes.
  // When buffer is NULL, the List is not able to grow and success() returns
  // false. This is used to identify bad memory allocations and parsing
  // failures.
  // This is in fact a constructor, but since we can't rely on the placement new
  // (issues #40, #45, #46), it's better to rely on a regular method
  void init(JsonBuffer *buffer) {
    _buffer = buffer;
    _firstNode = NULL;
  }

  node_type *createNode() {
    if (!_buffer) return NULL;
    return _buffer->create<node_type>();
  }

  void addNode(node_type *nodeToAdd) {
    if (_firstNode) {
      node_type *lastNode = _firstNode;
      while (lastNode->next) lastNode = lastNode->next;
      lastNode->next = nodeToAdd;
    } else {
      _firstNode = nodeToAdd;
    }
  }

  void removeNode(node_type *nodeToRemove);

  JsonBuffer *_buffer;
  node_type *_firstNode;
};
}
}
