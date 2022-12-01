#pragma once
#include <thread>
#include <malloc.h>
#include <mutex>
#include <stdlib.h>
#include <functional>
#include <stdexcept>

namespace Sp {
	template<class T>
	class Cell
	{
	public:
		T raw;

		T* operator*()
		{
			return &raw;
		};

	public:
		Cell* prev = nullptr;
		Cell* next = nullptr;
	};

	template<class T>
	class Iterator 
	{
	public:
		Iterator(Cell<T>* obj)
		{
			this->cell = obj;
		};

		Iterator& operator ++()
		{
			this->cell = cell->next;
			return *this;
		}

		Iterator operator ++(int)
		{
			Iterator temp = *this;
			cell = cell->next;
			return temp;
		}

		Iterator& operator --()
		{
			cell = cell->prev;
			return *this;
		}

		Iterator operator --(int)
		{
			Iterator temp = *this;
			this->cell = cell->prev;
			return temp;
		}

		T operator*() {
			return cell->raw;
		}

		T* operator&() {
			return &cell->raw;
		}

		Cell<T>* cell = nullptr;
	};

	template<class T>
	class List
	{
	public:
		~List() { Clear(); }

		Iterator<T> PushFront(T obj) {
			Cell<T>* front;
			front = new Cell<T>;
			front->raw = obj;
			front->prev = nullptr;
			front->next = endAndStart.next;

			if (endAndStart.next) {
				endAndStart.next = front;
			}
			else {
				endAndStart.prev = front;
			}

			return Iterator<T>(front);
		};

		Iterator<T> PushBack(T obj) {
			Cell<T>* back;
			back = new Cell<T>();
			back->raw = obj;
			back->prev = endAndStart.prev;
			back->next = nullptr;

			if (endAndStart.prev) {
				endAndStart.prev->next = back;
			}
			else {
				endAndStart.next = back;
			}

			endAndStart.prev = back;

			return Iterator<T>(back);
		};

		T* Insert(size_t index, T& obj) {
			if (index >= Size()) { return &PushBack(obj).cell->raw; }
			
			Iterator<T> itr = Begin();
			for (int i = 0; i < index; i++) {
				itr++;
			}

			return InsertOn(itr, obj);
		};

		T* InsertOn(Iterator<T>& itr, T& obj) {
			Cell<T>* cell = itr.cell;
			if (cell == nullptr) {
				return &PushBack(obj);
			}

			if (cell->prev == nullptr) {
				return &PushFront(obj);
			}

			Cell<T>* newCell;
			newCell = new Cell<T>();
			newCell->raw = obj;
			newCell->prev = cell->prev;
			newCell->next = cell;

			cell->prev->next = newCell;

			cell->prev = newCell;

			itr = Iterator<T>(newCell);
		};

		Iterator<T> Erase(Iterator<T> itr) {
			Cell<T>* cell = itr.cell;
			Iterator<T> ret(cell->next);
			if (cell->next) {
				cell->next->prev = cell->prev;
			}
			else
			{
				endAndStart.prev = cell->prev;
			}

			if (cell->prev) {
				cell->prev->next = cell->next;
			}
			else
			{
				endAndStart.next = cell->next;
			}

			delete cell;

			return ret;
		};

		void ForEach(std::function<void(T&)> process) {
			if (endAndStart.next == nullptr) { return; }
			Iterator<T> itr = Begin();
			while (itr.cell) {
				process(itr.cell->raw);
				itr++;
			}
		};

		void RemoveIf(std::function<bool(T&)> condition) {
			Iterator<T> itr(Begin());
			while (itr.cell) {
				if (condition(itr.cell->raw))
				{
					itr = Iterator<T>(Erase(itr));
				}
				else
				{
					itr++;
				};
			}
		};

		void Clear() {
			while (endAndStart.next)
			{
				Erase(Iterator<T>(endAndStart.next));
			}
		};

		Iterator<T> Begin() {
			return Iterator<T>(endAndStart.next);
		};

		Iterator<T> End() {
			return Iterator<T>(endAndStart.prev);
		};

		T* At(size_t index) throw (std::out_of_range) {
			Iterator<T> ret = Begin();
			for (int i = 0; i < index; i++) {
				ret++;
			}

			if (ret.cell == nullptr) {
				throw (std::out_of_range(""));
			}

			return &ret.cell->raw;
		};

		T& operator[](size_t index) throw (std::out_of_range) {
			return *At(index);
		};

		size_t Size() {
			size_t i = 0;
			ForEach([&](auto& o) { i++; });

			return i;
		}
		
	private:
		Cell<T> endAndStart;
	};

	template<class T>
	class SafeList
	{
	public:
		void Access(std::function<void(List<T>)> process) {
			std::lock_guard<std::mutex> lock(mtx);
			process(list);
		};

	private:
		List<T> list;
		std::mutex mtx;
	};
}
