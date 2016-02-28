#ifndef __ACTIVITY_H__
#define __ACTIVITY_H__

#include "common.h"
#include "Screen.h"

typedef class CActivity * Activity;

class CActivity
{
    private:
        static Activity Instance;

		Screen screen;

    public:
        int main( int argc, _TCHAR **argv );
	private:
        int initialize();
        int finalize();


    public:
        static inline Activity
        GetInstance(void)
        {
            if (!Instance) {
                Instance = new CActivity();
            }
            return Instance;
        }
};

#endif /* __ACTIVITY_H__ */