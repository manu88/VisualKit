//
//  VKButton.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKButton_hpp
#define VKButton_hpp

#include "../../GX/include/GXLayer.hpp"

class VKButton : public GXLayer
{
    
public:
    VKButton();
    virtual ~VKButton();
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
private:
};

#endif /* VKButton_hpp */
