//
//  VKLayout.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 30/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKLayout_hpp
#define VKLayout_hpp

#include "VKView.hpp"

class VKLayout : public VKView
{
public:
    
    typedef enum
    {
        Horizontal, // default
        Vertical
    } Direction;
    
    static constexpr const float DefaultSpacing = 20.f;
    
    
    VKLayout( VKLayout::Direction direction = Horizontal  );
    
    bool addChild( GXLayer* layer) override;

    void  setSpacing( float val) noexcept;
    float getSpacing() const noexcept
    {
        return _spacing;
    }
    
    void setDirection( VKLayout::Direction ) noexcept;
    VKLayout::Direction getDirection() const noexcept
    {
        return _dir;
    }
    
protected:
    // temp debug
    void paint( GXContext* context , const GXRect& bounds) override;
    
private:
    
    void buildConstrains();
    Direction _dir;
    float _spacing;
};

#endif /* VKLayout_hpp */
