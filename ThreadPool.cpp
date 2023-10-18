#include <iostream>
#include <queue>
#include <string>
#include <functional>
#include <future>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <map>
template<typename T>
class SafeQueue
{
public:

    T& front()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return task_queue_.front();
    }
    void push(const T& t)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        task_queue_.emplace(t);
    }
    void pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        task_queue_.pop();
    }
    size_t size()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return task_queue_.size();
    }
    bool empty()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return task_queue_.empty();
    }
    private:
        std::queue<T> task_queue_;
        std::mutex mutex_;
};

template<typename KEY, typename VALUE>
class SafeMap
{
    typedef typename std::map<KEY,VALUE>::iterator iterator;
    public:
    void erase(KEY key)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        map_.erase(key);
    }
    std::pair<iterator, bool>
    insert(KEY key, VALUE val)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return map_.insert({key, val});
    }
    size_t size()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return map_.size();
    }
    bool empty()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return map_.empty();
    }
    private:
    std::map<KEY, VALUE> map_;
    std::mutex mutex_;
};

class Task
{
public:
    typedef enum{
        WAIT,
        FINISH,
        ERROR,
        RUNNING
    }task_state_t;
    Task(std::string task_id) : task_id_(task_id) {}
    void exec()
    {
        if (func_)
        {
            func_();
        }
    }
        void set_state(task_state_t state) {state_ = state;}
        void set_task_id(std::string task_id) {task_id_ = task_id;}
        void set_func(std::function<void()> func) {func_ = func;}
        task_state_t get_state() const {return state_;}
        std::string get_task_id() const {return task_id_;}
    private:
        std::string task_id_;
        task_state_t state_ = WAIT;
        std::function<void()> func_;
        
};

class ThreadPool
{
public:
    ThreadPool(int thread_num = 4)
    {
        shut_down_ = false;
        for(int i = 0; i< thread_num; ++i)
        {
            thread_list_.emplace(std::thread(&ThreadPool::work_thread, this));
        }
    }
    ~ThreadPool()
    {
        while(!thread_list_.empty())
        {
            thread_list_.front().join();
            thread_list_.pop();
        }

    }
    void work_thread()
    {
        while(!shut_down_)
        {
            //fetch task from task_list
            std::unique_lock<std::mutex> lock(mutex_);
            while(task_list_.empty())
            {
                cond_.wait(lock);
            }

            std::shared_ptr<Task> task = task_list_.front();
            task_list_.pop();
            task->set_state(Task::RUNNING);
            task->exec();
            task->set_state(Task::FINISH);
        }

    }
    template<typename FUNC, typename... Args>
    auto add_task(std::string task_id, FUNC && func, Args &&... args)->std::future<decltype(func(args...))>
    {
        //construct task object
        std::shared_ptr<Task> task_ref(new Task(task_id));
        //adopt function into void()
        std::function<decltype(func(args...))()> bind_func= std::bind(std::forward<FUNC>(func), std::forward<Args>(args)...);
        auto packaged_task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(bind_func);
        std::function<void()> task_func = [=]{
            (*packaged_task)();
        };
        task_ref->set_func(task_func);
        //push task into queue
        task_list_.push(task_ref);
        task_map_.insert(task_id, task_ref);
        //notify work thread
        cond_.notify_one();
        //return future of ret value
        return packaged_task->get_future();
    }
    void query_task(std::string task_id)
    {

    }
    void cancel_task(std::string task_id)
    {

    }
    void shut_down(){
        std::unique_lock<std::mutex> lock(mutex_);
        shut_down_ = true;
        cond_.notify_all();
    }

private:
    SafeQueue<std::shared_ptr<Task>> task_list_;
    SafeMap<std::string, std::shared_ptr<Task>> task_map_;
    std::queue<std::thread> thread_list_;
    std::atomic<bool> shut_down_;
    std::condition_variable cond_;
    std::mutex mutex_;
};


int add(int a, int b)
{
    return a+b;
}

int main()
{
    ThreadPool thread_pool;
    auto promise = thread_pool.add_task("UUID",add, 1, 3);
    std::cout << promise.get() << std::endl;
    return 1; 
}