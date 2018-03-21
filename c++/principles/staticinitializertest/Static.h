#ifndef STATIC_H
#define STATIC_H

#include <iostream>

namespace Static {

    class Task
    {
        static int task_static;
    public:
        static void incTaskStatic() { ++task_static; }
        static void decTaskStatic() { --task_static; }

    public:
        Task() { std::cout << "Task::Task: " << task_static << std::endl; }
        ~Task() { std::cout << "Task::~Task: " << task_static << std::endl; }
    };

    
    class Initializer {
    private:
        static int nifty_count;

    public:
        
        Initializer() {

            if( nifty_count++ == 0 ) {
                Task::incTaskStatic();
            }
        }

        ~Initializer() {
            if( --nifty_count == 0 ) {
                Task::decTaskStatic();
            }
        }

    };

}


namespace {

    Static::Initializer initializer;

}

#endif
