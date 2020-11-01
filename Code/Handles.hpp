#pragma once
#include<iostream>
#include<cstdlib>
#include<functional>

using std::cout;
using std::endl;
using std::function;



 //Memory free Check
class Allocate_Check
{
    public:
        ~Allocate_Check()
        {
            Check();
        }

        void Check()
        {   
            if (new_count != 0)
            {
                cout << "Error!" << endl;

                system("pause");
                throw;
            }
        }

        Allocate_Check& operator++()
        {
            ++new_count;
            return *this;
        }

        Allocate_Check& operator--()
        {
            --new_count;
            return *this;
        }

    private:
        int new_count = 0;
};



//HandleFunctions
template<typename ClassType>
class HandleFunction
{
    public:
        static ClassType* default_handle(size_t size)
        {
            size = size * 2;

            return (ClassType*)malloc(size);
        }


        static ClassType* Class_Handle(size_t size)
        {
            size = sizeof(ClassType*);

            return (ClassType*)malloc(size);
        }

        HandleFunction() = delete;
        ~HandleFunction() = delete;
};



//New_Handle_Set and get handle
template<typename T>
class New_Handles
{
        typedef function<T* (size_t size)> HandleFunc;

    public:
        void Set_Handles(HandleFunc New_func)
        {
            this->func = New_func;
        }


        T* Handle(size_t size)
        {
            return func(size);
        }
        

    private:
        HandleFunc func;
};