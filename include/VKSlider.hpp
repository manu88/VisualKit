//
//  VKSlider.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 04/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKSlider_hpp
#define VKSlider_hpp

#include "VKAction.hpp"
#include "VKView.hpp"

class VKSlider : public VKView , public VKSender
{
public:
    VKSlider();
    
    
    void setPosition( float p) noexcept;
    float getPosition() const noexcept
    {
        return _pos;
    }
private:
    void paint( GXContext* context , const GXRect& bounds) override;
    
    float _pos;
};

#endif /* VKSlider_hpp */
