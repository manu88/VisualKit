//
//  VKAction.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKAction_h
#define VKAction_h


#include <functional>


class VKSender
{
public:
    virtual ~VKSender(){}
    
    
protected:
    VKSender(){}
    
private:
    
};

namespace VKAction
{
    typedef std::function<void(VKSender*)> Action;
}

#endif /* VKAction_h */
