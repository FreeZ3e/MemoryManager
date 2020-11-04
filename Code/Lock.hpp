#pragma once
#include<iostream>
#include<mutex>

using std::mutex;
using std::lock_guard;

class Lock
{
	private:
		mutex Mute;

	public:
		inline void Get_Lock()
		{
			Mute.lock();
		}

		inline void Unlock()
		{
			Mute.unlock();
		}
};