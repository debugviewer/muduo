// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_ATOMIC_H
#define MUDUO_BASE_ATOMIC_H

#include <stdint.h>
#include <atomic>

namespace muduo
{
    typedef std::atomic<int32_t> AtomicInt32;
    typedef std::atomic<int64_t> AtomicInt64;
    typedef std::atomic<bool> AtomicBool;

}  // namespace muduo

#endif  // MUDUO_BASE_ATOMIC_H
