#ifndef Animation_H
#define Animation_H


class Animation {
    public:
        Animation() {};

        virtual unsigned long getInterval() = 0;
        virtual void step() = 0;
};

#endif