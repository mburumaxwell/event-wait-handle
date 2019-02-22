#include "EventWaitHandle.h"

EventWaitHandle::EventWaitHandle(bool initialState, bool autoReset) :
    _autoReset(autoReset),
    _isSet(initialState),
    _cond(_cond_mtx)
{

}

void EventWaitHandle::set()
{
    // acquire lock (as per docs)
    _cond_mtx.lock();
    
    // set status and notify waiters
    _isSet = true;
    _cond.notify_one();

    // release lock (as per docs)
    _cond_mtx.unlock();
}

void EventWaitHandle::reset()
{
    // acquire lock (as per docs)
    _cond_mtx.lock();

    // set status and notify waiters
    _isSet = false;
    _cond.notify_one();

    // release lock (as per docs)
    _cond_mtx.unlock();
}

bool EventWaitHandle::wait_one()
{
    // if the status is set then no need to wait
    if (_isSet)
    {
        // if auto reset is enabled, reset it (set false)
        // otherwise, wait for reset() function to be called (set to true)
        _isSet = !_autoReset;
        return true; // nothing more to do
    }

    // acquire lock (as per docs)
    _cond_mtx.lock();
    
    // Spurious notifications can occur so check to
    // make sure the condition has actually been met
    while (!_isSet)
    {
        _cond.wait();
    }
    
    // release lock (as per docs)
    _cond_mtx.unlock();

    // we successfully waited for one notification
    return true;
}
