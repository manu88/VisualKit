//
//  VKSlider.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 04/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKSlider.hpp"
#include "VK.hpp"

VKSlider::VKSlider():
valueDidChange(nullptr),
_pos(0.f)
{
    setClassName( "VKSlider");
    //setOpaque(false);
    background = GXColors::LightGray;
}

void VKSlider::setPosition( float p) noexcept
{
    _pos = p;
    
    
}

void VKSlider::paint( GXContext* context , const GXRect& bounds)
{
    context->moveTo(GXPointMake(0, getSize().height/2));
    
    context->lineTo(GXPointMake(getSize().width, getSize().height/2));
    
    context->setStrokeWidth(2.f);
    context->setStrokeColor(GXColors::Black);
    context->stroke();
    context->beginPath();
    context->addCircle( GXPointMake( getSize().width*_pos, (getSize().height /2) ), 10);
    context->setFillColor(GXColors::DarkGray);
    context->fill();
}

bool VKSlider::touchMoved( const GXTouch &t)
{
    setPosition( (float)t.center.x  / (float)getSize().width );
    
    
    setNeedsRedraw();
    if( valueDidChange)
        valueDidChange(this);
    return true;
}
/*
bool VKSlider::serialize( GB::VariantMap& obj) const
{
    return VKView::serialize(obj);
}
 */
