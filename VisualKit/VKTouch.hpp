//
//  VKTouch.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKTouch_hpp
#define VKTouch_hpp

#include "../../GX/include/GXGeometry.hpp"



struct GXTouch
{
    typedef enum
    {
        Began = 0,
        Moved = 1,
        Ended = 2
    } Phase;
    
    GXPoint center;
    Phase phase;
    
};

class VKTouchDelegate
{
public:
    virtual ~VKTouchDelegate()
    {}
    
protected:
    VKTouchDelegate()
    {}
    
    virtual bool touchBegan( const GXTouch &t);
    virtual bool touchEnded( const GXTouch &t);
    
};

#endif /* VKTouch_hpp */
