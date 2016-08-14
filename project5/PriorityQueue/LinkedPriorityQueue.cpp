#include "LinkedPriorityQueue.h"
#include <math.h>

LinkedPriorityQueue::LinkedPriorityQueue() {
    head = NULL;

}

LinkedPriorityQueue::~LinkedPriorityQueue() {

}

void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    PQNode* p = head;
    int cnt = 0;
    while (p != NULL) {
        if (p->value == value) {
            if (p->priority < newPriority) {
                throw ("ERROR!");
            }
            else {
                if (p == head) {
                    head->priority = newPriority;
                }
                PQNode* q = head;
                int cnt2 = 0;
                while (cnt2 < cnt-1) {
                    q = q->next;
                    cnt2++;
                }
                q->next = p->next;
                p->next = NULL;
                enqueue(p->value,newPriority);
                break;
            }
        }
        p = p->next;
        cnt ++;
    }
    if (p == NULL) {
        throw ("ERROR!");
    }
}

void LinkedPriorityQueue::clear() {    
    while (head) {
        PQNode* p = head;
        head = head->next;
        p->next = NULL;
        delete p;
    }
}

string LinkedPriorityQueue::dequeue() {
    if (head == NULL) {
        throw ("ERROR!");
    }
    PQNode* p = head;
    head = head->next;
    string res = p->value;
    p->next = NULL;
    delete p;
    return res;
}

void LinkedPriorityQueue::enqueue(string value, int priority) {
    PQNode* cur = new PQNode();
    cur->value = value;
    cur->priority = priority;
    if (head == NULL) {
        head = cur;
    }
    else {
        PQNode* p = head;
        int cntP = 0;
        while (p != NULL) {
            if (p->priority < cur->priority) {
                p = p->next;
                cntP ++;
            }
            else if (p->priority == cur->priority) {
                string strP = p->value;
                string strCur = cur->value;
                int minlens = min(strP.size(), strCur.size());
                int i;
                for (i = 0; i < minlens; i++) {
                    if (strP[i] == strCur[i]) {
                        continue;
                    }
                    else if (strP[i] < strCur[i]) {
                        p = p->next;
                        cntP ++;
                        break;
                    }
                    else {
                        if (p == head) {
                            cur->next = head;
                            head = cur;
                            break;
                        }
                        else {
                            PQNode* q = head;
                            int cntQ = 0;
                            while (cntQ < cntP - 1) {
                                q = q->next;
                                cntQ ++;
                            }
                            q->next = cur;
                            cur->next = p;
                            break;
                        }
                    }
                }
                if (i != minlens) {
                    if (cur->next == p) {
                        break;
                    }
                }
                else {
                    if (i == strP.size()) {
                        p = p->next;
                        cntP ++;
                    }
                    else if (i == strCur.size()) {
                        if (p == head) {
                            cur->next = head;
                            head = cur;
                            break;
                        }
                        else {
                            PQNode* q = head;
                            int cntQ = 0;
                            while (cntQ < cntP - 1) {
                                q = q->next;
                                cntQ ++;
                            }
                            q->next = cur;
                            cur->next = p;
                            break;
                        }
                    }
                }
            }
            else {
                if (p == head) {
                    cur->next = head;
                    head = cur;
                    break;
                }
                else {
                    PQNode* q = head;
                    int cntQ = 0;
                    while (cntQ < cntP - 1) {
                        q = q->next;
                        cntQ ++;
                    }
                    q->next = cur;
                    cur->next = p;
                    break;
                }
            }
        }
        if (p == NULL) {
            PQNode* q = head;
            int cntQ = 0;
            while (cntQ < cntP - 1) {
                q = q->next;
                cntQ ++;
            }
            q->next = cur;
            cur->next = p;
        }
    }

}

bool LinkedPriorityQueue::isEmpty() const {
    if (head == NULL) {
        return true;
    } else
        return false;
}

string LinkedPriorityQueue::peek() const {
    if (head == NULL) {
        throw ("ERROR!");
    }
    return head->value;
}

int LinkedPriorityQueue::peekPriority() const {
    if (head == NULL) {
        throw ("ERROR!");
    }
    return head->priority;
}

int LinkedPriorityQueue::size() const {
    int cnt = 0;
    PQNode* p = head;
    while (p != NULL) {
        cnt ++;
        p = p->next;
    }
    return cnt;
}

ostream& operator <<(ostream& out, const LinkedPriorityQueue& queue) {
    PQNode* p = queue.head;
    if (p == NULL)
        out << "{" << "}";
    else {
        out << "{";
        while (p->next != NULL) {
            out << "\"" << p->value << "\":" << p->priority << ", ";
            p = p->next;
        }
        out << "\"" << p->value << "\":" << p->priority << "}";
    }
    return out;
}

