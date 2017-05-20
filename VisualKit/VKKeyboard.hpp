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

typedef enum
{
    Default = 0,
    FrenchMac  = 1,
    FrenchPC   = 2
} VKKeyboardLayout;

static VKKeyboardLayout DefaultLayout = FrenchMac;

struct GXKey
{
    int key;
    int modifiers;
    
    bool isCharacter() const;
    std::string toStr( VKKeyboardLayout layout = DefaultLayout ) const ;
    
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