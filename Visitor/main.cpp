//
//  main.cpp
//  Visitor
//
//  Created by Eric Stradal on 10/12/14.
//  Copyright (c) 2014 Eric Stradal. All rights reserved.
//

#include <iostream>
#include "Manacher.h"

class Wheel;
class Engine;
class Hemi;
class Transmission;
class Car;
class CarVisitor;

class ICarElementVisitor {
public:
    virtual void visit(Wheel *wheel)=0;
    virtual void visit(Engine *engine)=0;
    virtual void visit(Hemi *engine)=0;
    virtual void visit(Transmission *transmission)=0;
    virtual void visit(Car *car)=0;
};

class ICarElement {
public:
    ICarElement(){};
    virtual void accept(ICarElementVisitor *visitor) = 0;
};

class Wheel:public ICarElement{
private:
    std::string *name;
public:
    Wheel(){ name = new std::string("");};
    Wheel(std::string param){ name = new std::string(param); };
    std::string getName(){ return *new std::string(*this->name); };
    virtual void accept(ICarElementVisitor *visitor){ visitor->visit(this); };
};

class Engine:public ICarElement{
public:
    virtual void accept(ICarElementVisitor *visitor){ visitor->visit(this); };
};

class Hemi:public Engine{
public:
    virtual void accept(ICarElementVisitor *visitor){ visitor->visit(this); };
};

class Transmission:public ICarElement{
public:
    virtual void accept(ICarElementVisitor *visitor){ visitor->visit(this); };
};

class Car:public ICarElement{
public:
    Wheel *frontLeft, *frontRight, *rearLeft, *rearRight;
    Engine *engine;
    Transmission *transmission;

    Car(Engine *engineP){
        frontLeft = new Wheel("front left");
        frontRight = new Wheel("front right");
        rearLeft = new Wheel("rear left");
        rearRight = new Wheel("rear right");
        engine = engineP;
        transmission = new Transmission();
    }
    virtual void accept(ICarElementVisitor *visitor){ visitor->visit(this); };
};

class CarVisitor1:public ICarElementVisitor {
public:
    virtual void visit(Wheel *wheel){ std::cout << "wheel " << wheel->getName() << "\n"; }
    virtual void visit(Engine *engine){ std::cout << "engine\n"; }
    virtual void visit(Hemi *engine){std::cout << "hemi\n"; }
    virtual void visit(Transmission *transmission){ std::cout << "transmission\n"; }
    virtual void visit(Car *car){
        std::cout << "car\n";
        car->engine->accept(this);
        car->transmission->accept(this);
        car->frontLeft->accept(this);
        car->frontRight->accept(this);
        car->rearLeft->accept(this);
        car->rearRight->accept(this);
    }
};

class CarVisitor2:public ICarElementVisitor {
public:
    virtual void visit(Wheel *wheel){ std::cout << "goo wheel " << wheel->getName() << "\n"; }
    virtual void visit(Engine *engine){ std::cout << "goo engine\n"; }
    virtual void visit(Hemi *engine){std::cout << "goo hemi\n"; }
    virtual void visit(Transmission *transmission){ std::cout << "goo transmission\n"; }
    virtual void visit(Car *car){
        std::cout << "goo car\n";
        car->engine->accept(this);
        car->transmission->accept(this);
        car->frontLeft->accept(this);
        car->frontRight->accept(this);
        car->rearLeft->accept(this);
        car->rearRight->accept(this);
    }
};

template <class T>
class EStack{
private:
    class ESElem{
    public:
        ESElem *_next;
        T *_item;
    };
    ESElem *_top;
public:
    EStack(){ _top = nullptr; }
    EStack(T *element){
        ESElem *temp = new ESElem();
        temp->_next=_top;
        temp->_item = element;
    }
    T *item(){ return ((this->_top != NULL) ? this->_top->_item : NULL); }
    EStack *push(T *element){
        ESElem *n = new ESElem();
        n->_next = this->_top;
        n->_item = element;
        this->_top = n;
        return this;
    }
    T *pop(){
        ESElem *temp = _top;
        if (temp == nullptr) {
            return nullptr;
        }
        T *ret = temp->_item;
        if (temp->_next == nullptr) {
            this->_top = nullptr;
        }else{
            this->_top = temp->_next;
        }
        delete temp;
        return ret;
    }
    void print(){
        ESElem *current = this->_top;
        if (!current) {
            std::cout << "\n";
        }
        std::cout << *current->_item;
        while ((current = current->_next)){
            std::cout << ", " << *current->_item;
        }
        std::cout << "\n";
    }
    void reverse(){
        ESElem *current, *prev, *next;
        ESElem *top = this->_top;
        if (top == nullptr){
            return;
        }
        current = top->_next;
        prev = top;
        while((current)){
            next = current->_next;
            current->_next = prev;
            prev = current;
            current = next;
        }
        this->_top = prev;
        top->_next = nullptr;
    }
};

void ePrint(int elem){
    std::cout << elem << "\n";
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Car *car = new Car(new Hemi);
    Car *car2 = new Car(new Engine);
    CarVisitor1 *visitor1 = new CarVisitor1();
    CarVisitor2 *visitor2 = new CarVisitor2();
    
    car->accept(visitor1);
    car2->accept(visitor2);
    
    EStack<std::string> *eee = new EStack<std::string>();
    std::string *first = new std::string("one");
    eee->push(first);
    
    std::cout << *eee->item() << "\n";
    
    eee = eee->push(new std::string("two"));
    eee = eee->push(new std::string("twoddd"));
    eee = eee->push(new std::string("twoggg"));
    eee = eee->push(new std::string("twobbb"));
    eee->print();
    eee->reverse();
    eee->print();
    
    
    std::string *loopString;
    while ((loopString = eee->pop())) {
        std::cout << *loopString << "\n";
        eee->pop();
    }
    
    
    EStack<std::string> *fff = new EStack<std::string>();
    fff->reverse();
    fff->push(new std::string("single"));
    fff->reverse();
    fff->print();
              
    
    
    std::string *palindromeTest = new std::string("abcbabe");
    Manacher *m = new Manacher(palindromeTest);
    std::vector<int> *temp = m->go();
    
    for (int i = 0; i < temp->size(); i++){
        std::cout << temp->at(i) << ",";
    }
    
    return 0;
}
