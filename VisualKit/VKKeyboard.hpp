//
//  VKKeyboard.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 20/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKKeyboard_hpp
#define VKKeyboard_hpp


#include <string>



struct GXKey
{
    int key;
    int modifiers;
    
    std::string toStr() const ;
};

class VKKeyboardDelegate
{
    friend class CLApplication; // temp
public:
    virtual ~VKKeyboardDelegate()
    {}
    
protected:
    VKKeyboardDelegate()
    {}
    
    virtual bool keyPressed( const GXKey &key);
    
};

#endif /* VKKeyboard_hpp */
