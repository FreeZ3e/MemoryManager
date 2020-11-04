#pragma once
#include<iostream>
#include<cstdlib>
#include"Lock.hpp"

template<int ObjSize , int ObjNum = 20, class LockType = Lock>
class MemoryPool
{
    private:
        //Node
        typedef struct MemoryNode
        {
            MemoryNode* Next;
            char data[ObjSize];
        }Node;

        Node* pHead;
        Lock lock;

    public:
        MemoryPool()
        {   
            pHead = new Node;
            pHead->Next = nullptr;

            ExpandMemory();
        }

        ~MemoryPool()
        {
            Node* ptr;

            while (pHead)
            {
                ptr = pHead->Next;

                delete pHead;
                pHead = ptr;
            }
        }

        void* alloc()
        {   
            lock.Get_Lock();

            void* back;

            if (!pHead)
            {
                ExpandMemory();
            }

            back = pHead;
            pHead = pHead->Next;

            lock.Unlock();
            return back;
        }

        void free(void* ptr)
        {
            lock.Get_Lock();

            Node* toNext = (Node*)ptr;

            toNext->Next = pHead;
            pHead = toNext;

            lock.Unlock();
        }

    private:
        void ExpandMemory()
        {
            Node* newNode = new Node;

            this->pHead = newNode;

            for (int i = 1; i < ObjNum; i++)
            {
                newNode->Next = new Node;
                newNode = newNode->Next;
            }newNode->Next = nullptr;
        }
};