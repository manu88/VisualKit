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
    VKStoryboard::createFromFile(this, "ColorView.xml" , this);
    
    
    /*
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
     */
    
    
}

void ColorPickerView::setColor( const GXColor &c)
{
    /*
    _red.setContent(std::to_string(c.r));
    _green.setContent(std::to_string(c.g));
    _blue.setContent(std::to_string(c.b));
    _alpha.setContent(std::to_string(c.a));
    
    _red.setNeedsRedraw();
    _green.setNeedsRedraw();
    _blue.setNeedsRedraw();
    _alpha.setNeedsRedraw();
     */

}

void ColorPickerView::colorEditEnded(VKSender* )
{
    /*
    _mainView->colorEditEnded( GXColorMake( std::stof( _red.getContent() ),
                                            std::stof( _green.getContent() ),
                                            std::stof( _blue.getContent() ),
                                            std::stof( _alpha.getContent() )));
     */
}

void ColorPickerView::onStoryboardAction(VKSender* sender)
{
    const VKSlider* slider = dynamic_cast<const VKSlider*>(sender);
    assert(slider);
    
    //printf("Slider '%s' val %f \n" , slider->identifier.c_str() ,  slider->getPosition() );
    
    _mainView->colorEditEnded(GXColorMake( dynamic_cast<VKSlider*>( getChildByIdentifier("rSlider"))->getPosition(),
                                           dynamic_cast<VKSlider*>( getChildByIdentifier("gSlider"))->getPosition(),
                                           dynamic_cast<VKSlider*>( getChildByIdentifier("bSlider"))->getPosition(),
                                           dynamic_cast<VKSlider*>( getChildByIdentifier("aSlider"))->getPosition()
                                          ));
}

bool ColorPickerView::serialize( GB::VariantMap& ) const
{
    return false;
}

