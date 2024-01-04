
#include <iostream>
#include <array>
#include <mutex>
#include <condition_variable>
#include <future>
#include <vector>
#include <atomic>

template <typename T, std::size_t N>
class FixedSizeQueue
{
public:
    FixedSizeQueue();
    FixedSizeQueue(const FixedSizeQueue &other) = delete;
    FixedSizeQueue& operator=(const FixedSizeQueue &other) = delete;

    void Enque(const T& src);
    void Deque(T *dest);

private:
    std::array<T, N> m_queue;
    std::mutex m_readMutex;
    std::mutex m_writeMutex;
    std::condition_variable m_readCond;
    std::condition_variable m_writeCond;
    std::size_t m_readIndex;
    std::size_t m_writeIndex;
    std::atomic<std::size_t> m_numOfElements;
};

int main(void)
{
    FixedSizeQueue<std::size_t, 25> queue;
    std::vector<std::future<void>> futures;
    std::atomic<std::size_t> counter(0);
    const std::size_t N = 10000;

    for (std::size_t i = 0; i < N; ++i)
    {
        futures.emplace_back(std::async(std::launch::async, 
        [i, &queue, &counter]()
        {
            if (i % 2 == 0)
            {
                std::size_t value = 0;
                queue.Deque(&value);
                if (0 != value % 2)
                {
                    counter.fetch_add(1, std::memory_order_relaxed);
                }
            }
            else
            {
                queue.Enque(i);
            }
        }));
    }

    for (auto &f : futures)
    {
        f.wait();
    }

    std::cout << "Result: ";
    std::cout << counter << ", ";
    ((N  / 2) == counter) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    return 0;
}

template <typename T, std::size_t N>
FixedSizeQueue<T, N>::FixedSizeQueue() : 
m_readIndex(0), m_writeIndex(0), m_numOfElements(0)
{}

template <typename T, std::size_t N>
void FixedSizeQueue<T, N>::Enque(const T& src)
{
    std::unique_lock<std::mutex> lock(m_writeMutex);
    m_writeCond.wait(lock, [this]
    {return (m_numOfElements.load(std::memory_order_relaxed) < N);});
    m_queue[m_writeIndex++] = src;
    m_writeIndex %= N;
    m_numOfElements.fetch_add(1, std::memory_order_relaxed);
    m_readCond.notify_one();
}

template <typename T, std::size_t N>
void FixedSizeQueue<T, N>::Deque(T *dest)
{
    std::unique_lock<std::mutex> lock(m_readMutex);
    m_readCond.wait(lock, [this]
    {return (m_numOfElements.load(std::memory_order_relaxed) > 0);});
    *dest = m_queue[m_readIndex++];
    m_readIndex %= N;
    m_numOfElements.fetch_sub(1, std::memory_order_relaxed);
    m_writeCond.notify_one();
}



