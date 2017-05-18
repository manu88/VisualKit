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

class VKView : public GXLayer
{
    
public:
    VKView();
    virtual ~VKView();
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
private:
};

#endif /* VKView_hpp */
