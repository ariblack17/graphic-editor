//
//  ECObserver.h
//
//
//  Created by Yufeng Wu on 2/27/20.
//
//

#ifndef ECOBERVER_H
#define ECOBERVER_H

#include <vector>
#include <algorithm>
#include <iostream>

//********************************************
// Observer design pattern: observer interface

class ECObserver
{
public:
    virtual ~ECObserver() {}
    virtual void Update() = 0;
};

//********************************************
// Observer design pattern: subject

class ECObserverSubject
{
public:
    ECObserverSubject() {}
    virtual ~ECObserverSubject() {}
    void Attach( ECObserver *pObs )
    {
        //std::cout << "Adding an observer.\n";
        //std::cout << "observer: " << pObs << std::endl;
        listObservers.push_back(pObs);
        //std::cout << "number of observers: " << listObservers.size() << std::endl;
    }
    void Detach( ECObserver *pObs )
    {
        listObservers.erase(std::remove(listObservers.begin(), listObservers.end(), pObs), listObservers.end());
    }
    void Notify()
    {
//std::cout << "Notify: number of observer: " << listObservers.size() << std::endl;
        //std::cout << "in notify. number observers: " << listObservers.size() << std::endl;
        for(unsigned int i=0; i<listObservers.size(); ++i)
        {
            listObservers[i]->Update();
            //std::cout << "notifying observer " << i << std::endl;
        }
    }
    // delete later !!
    int getSize() {
        return listObservers.size();
    }
    
private:
    std::vector<ECObserver *> listObservers;
};

// class KeyStroke

#endif
