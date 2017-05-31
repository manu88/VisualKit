//
//  ColorPickerView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 23/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "ColorPickerView.hpp"
#include "BuilderMainView.hpp"

ColorPickerView::ColorPickerView(BuilderMainView* mainView):
_mainView(mainView)
{
    _red.setSingleLine(true);
    _green.setSingleLine(true);
    _blue.setSingleLine(true);
    _alpha.setSingleLine(true);
    
    
    _red.setBounds(GXRectMake(10, 10, 40, 30));
    _green.setBounds(GXRectMake(60, 10, 40, 30));
    _blue.setBounds(GXRectMake(110, 10, 40, 30));
    _alpha.setBounds(GXRectMake(170, 10, 40, 30));
    
    addChild(&_red);
    
    addChild(&_green);
    addChild(&_blue);
    addChild(&_alpha);
    
    _red.editingEnded = std::bind(&ColorPickerView::colorEditEnded, this , std::placeholders::_1);
    _green.editingEnded = std::bind(&ColorPickerView::colorEditEnded, this , std::placeholders::_1);
    _blue.editingEnded = std::bind(&ColorPickerView::colorEditEnded, this , std::placeholders::_1);
    _alpha.editingEnded = std::bind(&ColorPickerView::colorEditEnded, this , std::placeholders::_1);
    
    
}

void ColorPickerView::setColor( const GXColor &c)
{
    _red.setContent(std::to_string(c.r));
    _green.setContent(std::to_string(c.g));
    _blue.setContent(std::to_string(c.b));
    _alpha.setContent(std::to_string(c.a));
    
    _red.setNeedsDisplay();
    _green.setNeedsDisplay();
    _blue.setNeedsDisplay();
    _alpha.setNeedsDisplay();

}

void ColorPickerView::colorEditEnded(VKSender* sender)
{
    _mainView->colorEditEnded( GXColorMake( std::stof( _red.getContent() ),
                                            std::stof( _green.getContent() ),
                                            std::stof( _blue.getContent() ),
                                            std::stof( _alpha.getContent() )));
}

bool ColorPickerView::serialize( GB::VariantMap& obj) const
{
    return false;
}

void ColorPickerView::paint( GXContext* context , const GXRect& bounds)
{


}
