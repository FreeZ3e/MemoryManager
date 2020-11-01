#pragma once
#include<iostream>
#include<cstdlib>


template<int ObjSize , int ObjNum = 20>
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
            void* back;

            if (!pHead)
            {
                ExpandMemory();
            }

            back = pHead;
            pHead = pHead->Next;

            return back;
        }

        void free(void* ptr)
        {
            Node* toNext = (Node*)ptr;

            toNext->Next = pHead;
            pHead = toNext;
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