#include "MutexLock.h"
MutexLock::MutexLock():isLocking_(false)
{
    CHECK(!pthread_mutex_init(&mutex_,NULL));
}
MutexLock::~MutexLock()
{
    assert(!isLocking());
    CHECK(!pthread_mutex_destroy(&mutex_));
}

void MutexLock::lock()
{
    CHECK(!pthread_mutex_lock(&mutex_))//先加锁再修改状态，保证以下赋值操作的原子性。
        isLocking_=true;
}

void MutexLock::unlock()
{
    isLocking_=false;//先修改状态在解锁，保证赋值操作的原子性。
    CHECK(!pthread_mutex_unlock(&mutex_));
}
