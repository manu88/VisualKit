//
//  VKCheckBox.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 20/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKCheckBox.hpp"


VKCheckBox::VKCheckBox():
stateChanged(nullptr),
_state(false),
_defaultState(false)
{
    setClassName("VKCheckBox");
    
    setSize(GXSizeMake(30, 30));
    background = GXColors::LightGray;
}

void VKCheckBox::setState( bool state)
{
    if( _state != state)
    {
        _state = state;
        setNeedsRedraw();
    }
    
    _state = state;
}

void VKCheckBox::paint( GXContext*  context, const GXRect& rect )
{
    context->beginPath();
    context->addRect(GXRectMake(5, 5, getSize().width - 10, getSize().height - 10) );
    context->setStrokeColor(GXColors::Black);
    context->stroke();
    
    if( _state)
    {
        context->beginPath();
        context->addRect(GXRectMake(8, 8, getSize().width - 16, getSize().height - 16) );
        context->setFillColor(GXColors::DarkGray);
        context->fill();
    }
}

bool VKCheckBox::touchEnded( const GXTouch &t)
{
    _state = !_state;
    setNeedsRedraw();
    
    if( stateChanged)
    {
        stateChanged(this);
    }
    return true;
}
bool VKCheckBox::serialize( GB::VariantMap& obj) const
{
    obj.insert(std::make_pair("state", _defaultState));
    
    return VKView::serialize(obj);
}
