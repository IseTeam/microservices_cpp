#ifndef BREAKER_HPP
#define BREAKER_HPP

#include <iostream>
#include <time.h>
#include <string>
#include <mutex>
#include <functional>

using namespace std;

// 状态设置
enum State{
    Open = 0,
    Half_Open = 1, 
    Closed = 2,
};

typedef int State;

const State StateClosed = 0;
const State StateHalfOpen = 1;
const State StateOpen = 2;

typedef int errorNode ;
// 处于half open 且请求数超出阈值
const errorNode ErrTooManyRequests = -1;
// CB处于open 状态时返回
const errorNode ErrOpenState = -2;


string toString(State s){
    switch (s){
        case StateClosed:
            return "closed";
        case StateHalfOpen:
            return "half-open";
        case StateOpen:
            return "open";
        default:
            return "unknown state";
    }
}

// 计数器
class Counts{
public:
    uint32_t Requests;
    uint32_t TotalSuccesses;
    uint32_t TotalFailures;
    uint32_t ConsecutiveSuccess;
    uint32_t ConsecutiveFailures;

 
    void onRequest(){
        this->Requests++;
    }

    void onSuccess(){
        this->TotalSuccesses++;
        this->ConsecutiveSuccess++;
        this->ConsecutiveFailures = 0;
    }
    void onFailure(){
        this->TotalFailures++;
        this->ConsecutiveFailures++;
        this->ConsecutiveSuccess = 0;
    }

    void clear(){
        this->Requests = 0;
        this->TotalSuccesses = 0;
        this->TotalFailures = 0;
        this->ConsecutiveSuccess = 0;
        this->ConsecutiveFailures = 0;
    }

};


// defer
#define CONNECTION(text1, text2) text1#text2
#define CONNECT(text1, text2) CONNECTION(text1, text2)
#define defer(code) Defer CONNECT(L, __LINE__) ([&](){code;})

class Defer{
private:
    std::function<void()> m_func;

public:
    Defer(std::function<void()> &&func) : m_func(std::move(func)){}
    ~Defer() {if (m_func) m_func();}
};


struct error{
    time_t time;
    string message;
};
struct Duration{
    time_t start_time;
    time_t end_time;
};

typedef bool (*funcTrip)(Counts counts);
typedef void (*funcChange)(string name, State from, State to);
typedef bool (*funcSuccess)(error err);

struct Setting{
    string Name;
    uint32_t MaxRequests;
    time_t Interval;
    time_t Timeout;
    funcTrip ReadyToTrip;
    funcChange OnStateChange;
    funcSuccess IsSuccessful;
};

const time_t defaultInterval = 0 ;
const time_t defaultTimeout = 60 ;


typedef void* (*Request)(void) ;

// Circuit Breaker的状态机
class CircuitBreaker{
    string name;
    uint32_t maxRequests;
    time_t Interval;
    time_t Timeout;
    funcTrip ReadyToTrip;
    funcChange OnStateChange;
    funcSuccess IsSuccessful;

    mutex mutex;
    State state;
    uint64_t generation;
    Counts counts;
    time_t expiry;

    public: 
        CircuitBreaker(Setting setting);
        string Name();
        State GetState();
        Counts Counts();
        void* Execute(Request request, error);
        uint64_t beforeRequest();
        void afterRequest(uint64_t , bool);
        void onSuccess(State state, time_t now);
        void onFailure(State state, time_t now);
        State currentState(time_t now);
        void setState(State state, time_t now);
        void toNewGeneration(time_t now);
};

class TwoStepCircuitBreaker{
    CircuitBreaker* cb;

    TwoStepCircuitBreaker(Setting setting){
        cb = new CircuitBreaker(setting);
    }

    string Name();
    State State();
    Counts Counts();
    
    (func(bool success) done, error) Alloc();

     
};


/* 构造函数，通过Setting配置新的CircuitBreaker */ 
CircuitBreaker::CircuitBreaker(Setting setting){
    //CircuitBreaker* cb = new(struct CircuitBreaker);

    this->name = setting.Name;
    this->OnStateChange = setting.OnStateChange;

    if(setting.MaxRequests == 0){
        this->maxRequests = 1;
    }else{
        this->maxRequests == setting.MaxRequests;
    }

    if(setting.Interval <= 0){
        this->Interval = defaultInterval;
    }else{
        this->Interval == setting.Interval;
    }

    if(setting.Timeout <= 0){
        this->Timeout = defaultTimeout;
    }else{
        this->Timeout = setting.Timeout;
    }

    if(setting.ReadyToTrip == NULL){
        this->ReadyToTrip = defaultReadyToTrip;
    }else{
        this->ReadyToTrip = setting.ReadyToTrip;
    }

    if(setting.IsSuccessful == NULL){
        this->IsSuccessful = defaultIsSuccessful;
    }else{
        this->IsSuccessful = setting.IsSuccessful;
    }
    // 生成当前时间并存储
    this->toNewGeneration(time(NULL));
}

bool defaultReadyToTrip(Counts counts) {
    return counts.ConsecutiveFailures > 5;
}

bool defaultIsSuccessful(error err) {
    return err == NULL;
}

string CircuitBreaker::Name(){
    return name;
}

State CircuitBreaker::GetState(){
    mutex.lock();
    
    time_t now = time(NULL);        // 现在的时间
    
    state = currentState(now);

    mutex.unlock();
    return state;
}

Counts CircuitBreaker::Counts(){
    mutex.lock();

    defer( mutex.unlock() );
    return counts;
}

typedef void (*done)(bool);

// 检测是否可以继续进行新的request，返回用于注册success或failure的调用，否则返回错误
done TwoStepCircuitBreaker::Allow(){
    generation = cb.beforeRequest();

}

uint64_t beforeRequest(){
    mutex.lock();
    defer(mutex.unlock());
    

    

    return generation
}


#endif
