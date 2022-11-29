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
			this->cell = cell->next();
		}

		Iterator& operator --()
		{
			this->cell = cell->prev();
		}

		T operator*() {
			return cell->raw;
		}

		Cell<T>* operator->() {
			return cell;
		}

	private:
		Cell<T>* cell;
	};

	template<class T>
	class List
	{
	public:
		Iterator<T> PushFront(T obj) {
			Cell<T>* front;
			front = (Cell<T>*)malloc(sizeof(Cell<T>));
			front->raw = obj;
			front->prev = nullptr;
			front->next = endAndStart.next;

			if (endAndStart.next) {
				endAndStart.next = front;
			}

			return Iterator<T>(front);
		};

		Iterator<T> PushBack(T obj) {
			Cell<T>* back;
			back = (Cell<T>*)malloc(sizeof(Cell<T>));
			back->raw = obj;
			back->prev = endAndStart.prev;
			back->next = nullptr;

			if (endAndStart.prev) {
				endAndStart.prev.next = back;
			}

			return Iterator<T>(back);
		};

		T* Insert(size_t index, T& obj) {
			if (index >= Size()) { return PushBack(obj); }
			
			Iterator<T> itr = Begin();
			for (int i = 0; i < index; i++) {
				itr++;
			}

			return InsertOn(itr, obj);
		};

		T* InsertOn(Iterator<T>& itr, T& obj) {
			Cell<T> cell = itr.cell;
			if (cell == nullptr) {
				return PushBack(obj);
			}

			if (cell->prev == nullptr) {
				return PushFront(obj);
			}

			Cell<T>* newCell;
			newCell = (Cell<T>*)malloc(sizeof(Cell<T>));
			newCell->raw = obj;
			newCell->prev = cell.prev;
			newCell->next = cell;

			cell->prev->next = newCell;

			cell->prev = newCell;

			itr = Iterator<T>(newCell);
		};

		Iterator<T> Erase(Iterator<T>* itr) {
			Cell<T>* cell = itr->cell;
			Iterator<T>* ret(cell->next);
			if (cell->next) {
				cell->next->prev = cell->prev;
			}

			if (cell->prev) {
				cell->prev->next = cell->next;
			}

			delete cell;

			return ret;
		};

		void ForEach(std::function<void(T)> process) {
			Iterator<T> itr(Begin());
			while (itr) {
				process(itr->raw);
				itr++;
			}
		};

		void RemoveIf(std::function<bool(T)> condition) {
			Iterator<T> itr(Begin());
			while (itr) {
				if (process(itr->raw))
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
			RemoveIf(
				[&](auto& o) {
					return true;
				}
			);
		};

		Iterator<T>* Begin() {
			return Iterator<T>(endAndStart.next);
		};

		Iterator<T>* End() {
			return Iterator<T>(endAndStart.prev);
		};

		T* At(size_t index) throw (std::out_of_range) {
			Iterator<T>* ret = Begin();
			for (int i = 0; i < index; i++) {
				ret++;
			}

			if (ret->cell == nullptr) {
				throw std::out_of_range;
			}

			return &ret->cell->raw;
		};

		T& operator[](size_t index) throw (std::out_of_range) {
			return At(index);
		};

		size_t Size() {
			size_t i = 0;
			ForEach([](auto& o) { i++; });

			return i;
		}
		
	private:
		size_t size;

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
