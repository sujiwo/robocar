#ifndef MR_RING_BUFFER_H_
#define MR_RING_BUFFER_H_

#include <cstdio>
#include <vector>
#include <memory>
#include <pthread.h>

//#include "globals.h"
//#include "utils.h"

typedef unsigned char byte_t;
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)


typedef unsigned char byte_t;

//namespace miuro { namespace internal {


class RingBuffer {
  public:
    explicit RingBuffer(unsigned int size);
    ~RingBuffer();


    /// Push 1 byte
    bool Push(byte_t datum);
    /**
     * @param[in] data
     */
    bool PushRange(const std::vector<byte_t>& data);

    bool PushRange(const byte_t* data, unsigned int size);

    /// Read 1 byte from the head without consumption.
    bool Peek(byte_t* out_datum);

    /// Shift 1 byte
    bool Shift(byte_t* out_datum);
    /**
     *
     * @param[out] out_data
     */
    bool ShiftRange(std::vector<byte_t>* out_data);

    bool ShiftRange(byte_t* out_data, unsigned int size);

    /**
     *
     */
    unsigned int GetDataLength() const;
    /**
     *
     */
    unsigned int GetSpaceLength() const;
    /**
     *
     */
    void Clear();

    void GetToken(char* out_data,
                  char delim,
                  int max_size,
                  int* out_read_size);

    void GetTokenLength(char delim, int* out_read_size);

    unsigned int size() const { return size_; }
    const std::vector<byte_t>& buffer() const { return buffer_; }
    unsigned int read_cursor() const { return read_cursor_; }
    unsigned int write_cursor() const { return write_cursor_; }

  private:
    unsigned int size_;
    std::vector<byte_t> buffer_;
    unsigned int read_cursor_;
    unsigned int write_cursor_;

    DISALLOW_COPY_AND_ASSIGN(RingBuffer);
};

/**
 *
 */
class LockPolicyNoLock {
  public:
    void Lock();
    void Unlock();
  private:
    DISALLOW_COPY_AND_ASSIGN(LockPolicyNoLock);
};

#if 0
/**
 *
 */
class LockPolicyMutex {
  public:
    LockPolicyMutex() : mutex_() { }

    ~LockPolicyMutex() {
    }

    void Lock();
    void Unlock();
  private:
    Mutex mutex_;
    DISALLOW_COPY_AND_ASSIGN(LockPolicyMutex);
};

#endif

/**
 *
 */
template <typename Value, int SIZE, typename LockPolicy = LockPolicyNoLock>
    class QueueBase {
      public:
        explicit QueueBase()
            : buffer_(SIZE + 1)
            , read_cursor_(0)
            , write_cursor_(0) {

        }

        ~QueueBase() { }

        bool Enqueue(const Value& value) {
            locker_.Lock();

            if (GetCount() >= SIZE - 1) {
                locker_.Unlock();
                return false;
            }
            buffer_[write_cursor_++] = value;
            write_cursor_ %= SIZE + 1;

            locker_.Unlock();
            return true;
        }

        bool Dequeue(Value* value) {
            locker_.Lock();

            if (GetCount() < 1) {
                locker_.Unlock();
                return false;
            }
            *value = buffer_[read_cursor_++];
            read_cursor_ %= SIZE + 1;

            locker_.Unlock();
            return true;
        }

        unsigned int GetCount() const {
            int len = write_cursor_ - read_cursor_;
            if (len < 0) {
                len += SIZE + 1;
            }
            return len;
        }

        void Clear() {
            locker_.Lock();
            read_cursor_ = 0;
            write_cursor_ = 0;
            locker_.Unlock();
        }

        unsigned int size() const { return SIZE; }
      private:
        LockPolicy locker_;
        std::vector<Value> buffer_;
        unsigned int read_cursor_;
        unsigned int write_cursor_;

        DISALLOW_COPY_AND_ASSIGN(QueueBase);
    };



#endif/*MR_RING_BUFFER_H_*/

