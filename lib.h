#ifndef _lib_h
#define _lib_h

#include <assert.h>
#include <pthread.h>

#define Pthread_mutex_unlock(m) assert(pthread_mutex_unlock(m) == 0)
#define Pthread_create(thread, attr, start_routine, arg)                       
  assert(pthread_create(thread, attr, start_routine, arg) == 0)
#define Pthread_mutex_init(m, attr) assert(pthread_mutex_init(m, attr) == 0)


#define Pthread_mutex_lock(m) assert(pthread_mutex_lock(m) == 0)

#define Pthread_join(thread, value_ptr)                                        
  assert(pthread_join(thread, value_ptr) == 0)
#endif
