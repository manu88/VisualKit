//
//  VKView.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKView_hpp
#define VKView_hpp

#include "../../GX/include/GXLayer.hpp"
#include "VKTouch.hpp"

class VKView : public GXLayer , public VKTouchDelegate
{
    friend class CLApplication;
public:
    VKView();
    virtual ~VKView();
protected:
    
    
    bool touchBegan( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
private:
    
    
};

#endif /* VKView_hpp */
