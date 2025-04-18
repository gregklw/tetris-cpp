// evh_native.cpp
#include <stdio.h>

//[event_source(native)]
class CSource {
public:
    __event void MyEvent(int nValue); //delegate
};

//[event_receiver(native)]
class CReceiver {
public:
    //event handler (how to handle/respond to event once it's triggered)
    void MyHandler1(int nValue) {
        printf_s("MyHandler1 was called with value %d.\n", nValue);
    }

    void MyHandler2(int nValue) {
        printf_s("MyHandler2 was called with value %d.\n", nValue);
    }

    //subscribe event handler to delegate
    void hookEvent(CSource* pSource) {
        __hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
        __hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
    }

    //unsubscribe event handler to delegate
    void unhookEvent(CSource* pSource) {
        __unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
        __unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
    }
};