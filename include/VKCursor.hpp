//
//  VKCursor.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKCursor_hpp
#define VKCursor_hpp

#include "../../GX/include/GXLayer.hpp"

class  VKCursor : public GXLayer
{
public:
    VKCursor();
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
};

#endif /* VKCursor_hpp */
