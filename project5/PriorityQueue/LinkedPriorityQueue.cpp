// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "LinkedPriorityQueue.h"

LinkedPriorityQueue::LinkedPriorityQueue() {
    // TODO: implement this constructor

}

LinkedPriorityQueue::~LinkedPriorityQueue() {
    // TODO: implement this destructor

}

void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    // TODO: implement this member
}

void LinkedPriorityQueue::clear() {
    // TODO: implement this member
}

string LinkedPriorityQueue::dequeue() {
    // TODO: implement this member
    return "";   // remove this
}

void LinkedPriorityQueue::enqueue(string value, int priority) {
    // TODO: implement this member
}

bool LinkedPriorityQueue::isEmpty() const {
    // TODO: implement this member
    return false;   // remove this
}

string LinkedPriorityQueue::peek() const {
    // TODO: implement this member
    return "";   // remove this
}

int LinkedPriorityQueue::peekPriority() const {
    // TODO: implement this member
    return 0;   // remove this
}

int LinkedPriorityQueue::size() const {
    // TODO: implement this member
    return 0;   // remove this
}

ostream& operator <<(ostream& out, const LinkedPriorityQueue& queue) {
    // TODO: implement this operator
    return out;
}
