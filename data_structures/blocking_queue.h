//
//  blocking_queue.h
//  Algorithms
//
//  Created by longjianjiang on 2019/3/3.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef blocking_queue_h
#define blocking_queue_h

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace jiang {
#define DEFAULT_BLOCKING_QUEUE_SIZE 100

	template <typename T, typename Container = std::queue<T>>
	class blocking_queue {
	public:
		using container_type			= Container;
		using value_type				= typename Container::value_type;
		using reference 				= typename Container::reference;
		using size_type 				= typename Container::size_type;
		using mutex_type				= std::mutex;
		using condition_variable_type 	= std::condition_variable;

	private:
		container_type 			_queue;
		mutex_type				_mutex;
		condition_variable_type	_cond;

	public:
		blocking_queue() = default;
		void push(const value_type& data);
		void push(value_type&& data);
		void pop(reference data);
		bool try_pop(reference data);
		bool empty() const;
		size_type size();// const { return _queue.size(); }
	};

    template <typename T, typename Container>
	void blocking_queue<T, Container>::push(const value_type& data) {
		{
			std::lock_guard<mutex_type> lock(_mutex);
			_queue.push(data);
		}
		_cond.notify_one();
	}

	template <typename T, typename Container>
	void blocking_queue<T, Container>::push(value_type&& data) {
		{
			std::lock_guard<mutex_type> lock(_mutex);
			_queue.push(std::move(data));
		}
		_cond.notify_one();
	}

	template <typename T, typename Container>
	void blocking_queue<T, Container>::pop(reference data) {
		std::unique_lock<mutex_type> lock(_mutex);
		_cond.wait(lock, [this]() {return !_queue.empty();} );
		data = std::move(_queue.front());
		_queue.pop();
	}

	template <typename T, typename Container>
	bool blocking_queue<T, Container>::try_pop(reference data) {
		std::unique_lock<mutex_type> lock(_mutex);
		if (_queue.empty()) {
			return false;
		}
		data = std::move(_queue.front());
		_queue.pop();
		return true;
	}

	template <typename T, typename Container>
	bool blocking_queue<T, Container>::empty() const {
		std::lock_guard<mutex_type> lock(_mutex);
		return _queue.empty();
	}

	// template <typename T, typename Container>
	// size_type blocking_queue<T, Container>::size() const {
	// 	std::lock_guard<mutex_type> lock(_mutex);
	// 	return _queue.size();
	// }

}
#endif /* blocking_queue_h */