# MemoryManager

#### 介绍
简单的内存池和用于new函数的handle实现,并提供了对delete使用次数的检测.

#### 架构
        Handles.hpp和MemoryPool.hpp分别是handle函数和内存池,主要用于类中重载operator new和operator new[]以及delete,delete[]的定制实现

        Hendles.hpp:
                    Allocate_Check类用于对delete次数的检测,若不符合则会抛出异常.
                    
                    HandleFunction类提供了用于operator new的handle函数.
    
                    New_Handles类提供了一个函数指针,用于重新设置handles函数.

        
        MemoryPool.hpp:简单的内存池实现.
                    