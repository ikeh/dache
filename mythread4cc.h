
#include <pthread.h>
#ifndef _MYTHREAD4CC_H_
#define _MYTHREAD4CC_H_

class Mypthread4cc
{
	public:
		Mypthread4cc ();
        virtual ~Mypthread4cc () = 0;
        void start();
        virtual void run() = 0;
    private:
        pthread_t pid;
};

void* threadFunc(void* paramxd)
{       
    Mypthread4cc* Mypthread4cc = (Mypthread4cc*)paramxd;
    Mypthread4cc->run();
    return 0;
}

Mypthread4cc::Mypthread4cc(){}

Mypthread4cc::~Mypthread4cc(){}

void Mypthread4cc::start()
{
	pthread_create(&pid,NULL,threadFunc,this);
}

/*********************************************************************/
/*
class threadxd:public Mypthread4cc
{
	public:
		threadxd(){}

		~threadxd(){}

		void run()
		{
			Datacache::syn_to_dbxd();
		}
};
*/
#endif
