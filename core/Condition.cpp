//
// Created by suncx on 2020/8/9.
//

#include "Condition.h"

Condition::Condition(Mutex &mutex) : mutex(mutex) {
    auto status = pthread_cond_init(&cond, nullptr);
    if (unlikely(status != 0)) ERROR_EXIT("error occurred.");
}

Condition::~Condition() {
    auto status = pthread_cond_destroy(&cond);
    if (unlikely(status != 0)) ERROR_EXIT("error occurred.");
}

void Condition::wait() {
    int status;
    Mutex::ConditionWaitGuard guard(mutex);
    status = pthread_cond_wait(&cond, mutex.get_mutex());
    if (unlikely(status != 0)) ERROR_EXIT("error occurred.");
}

bool Condition::timed_wait(double seconds) {
    timespec ts;
    auto status = clock_gettime(CLOCK_REALTIME, &ts);
    if (unlikely(status != 0)) ERROR_EXIT("error occurred.");
    //TODO: seconds is double, not int
    ts.tv_sec += seconds;

    Mutex::ConditionWaitGuard guard(mutex);
    return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get_mutex(), &ts);
}

void Condition::notify() {
    auto status = pthread_cond_signal(&cond);
    if (unlikely(status != 0)) ERROR_EXIT("error occurred.");
}

void Condition::notify_all() {
    auto status = pthread_cond_broadcast(&cond);
    if (unlikely(status != 0)) ERROR_EXIT("error occurred.");
}

