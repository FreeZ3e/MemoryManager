#include"MemoryPool.hpp"
#include"Handles.hpp"
#include<iostream>
#include<cstdlib>


class test
{
    public:
        void* operator new(size_t size);

        void operator delete(void* ptr);
};

//MemoryPool
MemoryPool<sizeof(test)> MemObj;

//Handles
New_Handles<test> HandleObj;

//Check
Allocate_Check CheckObj;


//operator new and delete
void* test::operator new(size_t size)
{   
    void* ptr = MemObj.alloc();

    while (!ptr)
    {
        HandleObj.Set_Handles(HandleFunction<test>::Class_Handle);
        ptr = HandleObj.Handle(sizeof(ptr));
    }

    ++CheckObj;
    return ptr;
}

void test::operator delete(void* ptr)
{
    if (ptr)
    {   
        --CheckObj;
        MemObj.free(ptr);
    }
}

int main()
{
    test* p = new test();
    delete p;

    system("pause");
    return 0;
}