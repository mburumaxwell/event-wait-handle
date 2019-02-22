#ifndef __EVENT_WAIT_HANDLE_H
#define __EVENT_WAIT_HANDLE_H

#include "rtos/ConditionVariable.h"
#include "rtos/Mutex.h"

class EventWaitHandle {

public:
    EventWaitHandle(bool initialState, bool autoReset);

    void set();
    void reset();
    bool wait_one();

private:
    bool _autoReset, _isSet;
    rtos::Mutex _cond_mtx;
    rtos::ConditionVariable _cond;

};

#endif /* __EVENT_WAIT_HANDLE_H */
