// -*-c++-*-
#ifndef MINVR_DATAQUEUE_H
#define MINVR_DATAQUEUE_H

#include <string>
#include <map>
#include <sstream>
#include <iostream>


// This object maintains a queue (FIFO) of serialized VRDatum objects.
// Serialization turns them into strings, so this is basically just a
// queue of strings.  See the VRDataIndex object for more about these
// objects and their types as part of a system of named data values.
// Over here, we don't care so much about names, as about times of
// creation, and quick assembly and disassembly into serialized data.
//
// Use this queue for sending data to some other process, or receiving
// it.  The transmission format is the same XML format as in the
// VRDataIndex description.
//
// Tom Sgouros 10/16/2015
//
//
class VRDataQueue {
public:
    typedef std::string serialData;
  
private:

  typedef std::map<long long,serialData> VRDataList;
  VRDataList dataMap;
  
public:
  VRDataQueue() {};
  VRDataQueue(const serialData serializedQueue);

  static const serialData noData;
  
  void addSerializedQueue(const serialData serializedQueue);
  
  bool notEmpty() { return (bool)dataMap.size(); }

  // Returns the object at the head of the queue, but does not remove
  // it from the queue.
  serialData getSerializedObject();
  // Removed the object at the front of the queue.
  void pop();

  // Remove all the objects in the queue.
  void clear();
  
  // Takes a serialized bit of data and pushes it onto the end of the
  // queue.
  void push(const serialData serializedData);
  void push(const long long timeStamp, const serialData serializedData);

  // Serialize the whole queue into a piece of XML.  There is no
  // deserialize method, but there is a constructor that takes a serialized
  // queue as input.
  serialData serialize();

  // A debug-friendly output function.
  std::string printQueue(); 
  
};

#endif
