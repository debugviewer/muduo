// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_BLOCKINGQUEUE_H
#define MUDUO_BASE_BLOCKINGQUEUE_H

#include <deque>
#include <assert.h>
#include <mutex>
#include <condition_variable>
#include "muduo/base/noncopyable.h"

namespace muduo
{
// implement with c++11
template<typename T>
class BlockingQueue : noncopyable
{
public:
    BlockingQueue()
        : mutex_(),
          notEmpty_(),
          queue_()
    {
    }

    void put(const T& x) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push_back(x);
        notEmpty_.notify_one();
    }

    void put(T&& x) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push_back(std::move(x));
        notEmpty_.notify_one();
    }

    T take() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            notEmpty_.wait(lock);
        }

        assert(!queue_.empty());
        T front(std::move(queue_.front()));
        queue_.pop_front();
        return front;
    }

    size_t size() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.size();
    }
protected:
private:
    mutable std::mutex mutex_;
    std::condition_variable notEmpty_;
    std::deque<T> queue_;
};

}  // namespace muduo

#endif  // MUDUO_BASE_BLOCKINGQUEUE_H
