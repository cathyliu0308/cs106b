#include "TileStack.h"
#include "strlib.h"
#include "stack.h"

TileStack::TileStack() {
    front = NULL;


}

TileStack::~TileStack() {
    //delete front;
}

void TileStack::pushTile(int x, int y, int width, int height, string color) {
    if (front == NULL) {
        front = new TileNode(x,y,width,height,color);
    }
    else {
        TileNode* top = new TileNode();
        top->x = x;
        top->y = y;
        top->color = color;
        top->width = width;
        top->height = height;
        top->next = front;
        front = top;
    }
}

void TileStack::drawAll(GWindow& window) const {
    TileNode* p = front;
    while (p!= NULL) {
        p->draw(window);
        p = p->next;
    }
}

void TileStack::highlight(int x, int y) {
    TileNode* p = front;
    while (p!= NULL) {
        if ((x >= p->x) && (x <= p->x + p->width) && (y >= p->y) && (y <= p->y + p->height)) {
            p->color = "yellow";
            break;
        }
        p = p->next;
    }
}

void TileStack::raise(int x, int y) {
    TileNode* p = front;
    if (((x < front->x) || (x > front->x)) && ((y < front->y) || (y > front->y))) {
        while (p->next != NULL) {
            if ((x >= p->next->x) && (x <= p->next->x + p->next->width) && (y >= p->next->y) && (y <= p->next->y + p->next->height)) {
                TileNode* tmp = p->next;
                p->next = tmp->next;
                tmp->next = front;
                front = tmp;
                //delete tmp;
                break;
            }
            p = p->next;
        }
    }
}

void TileStack::remove(int x, int y) {
    TileNode* p = front;
    if (((x < front->x) || (x > front->x)) && ((y < front->y) || (y > front->y))) {
        while (p->next!= NULL) {
            if ((x >= p->next->x) && (x <= p->next->x + p->next->width) && (y >= p->next->y) && (y <= p->next->y + p->next->height)) {
                TileNode* tmp = p->next;
                p->next = p->next->next;
                delete tmp;
                break;
            }
            p = p->next;
        }
    }
    else {
        front = front->next;
        p->next = NULL;
        delete p;
    }
}

void TileStack::clear() {    
    while (front != NULL) {
        TileNode* p = front;
        front = front->next;
        p->next = NULL;
        delete p;
    }

}
