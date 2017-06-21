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
    getChildByIdentifierAs<VKSlider*>("rSlider")->setPosition(c.r);
    getChildByIdentifierAs<VKSlider*>("gSlider")->setPosition(c.g);
    getChildByIdentifierAs<VKSlider*>("bSlider")->setPosition(c.b);
    getChildByIdentifierAs<VKSlider*>("aSlider")->setPosition(c.a);
    

    getChildByIdentifierAs<VKSlider*>("rSlider")->setNeedsRedraw();
    getChildByIdentifierAs<VKSlider*>("gSlider")->setNeedsRedraw();
    getChildByIdentifierAs<VKSlider*>("bSlider")->setNeedsRedraw();
    getChildByIdentifierAs<VKSlider*>("aSlider")->setNeedsRedraw();
     

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
    assert(sender);
    const VKView* base = dynamic_cast<const VKView*>(sender);

    if( base->getClassName() == "VKSlider")
    {

    _mainView->colorEditEnded(GXColorMake( getChildByIdentifierAs<const VKSlider*>("rSlider")->getPosition(),
                                           getChildByIdentifierAs<const VKSlider*>("gSlider")->getPosition(),
                                           getChildByIdentifierAs<const VKSlider*>("bSlider")->getPosition(),
                                           getChildByIdentifierAs<const VKSlider*>("aSlider")->getPosition()
                                          ));
    }
    else if( base->identifier == "preset")
    {
        
        const VKDropDown* dp = dynamic_cast<const VKDropDown*>(sender);
        
        const auto colorName = dp->getSelectedItem();//.c_str();
        printf("Select preset color : '%s'\n" ,colorName.c_str() );
        
        
        if( GXColors::ColorsNames.count(colorName.c_str()))
        {
            _mainView->colorEditEnded( GXColors::ColorsNames.at( colorName ));
        }
        else
        {
            printf("Color '%s' not found \n" , colorName.c_str());
        }
    }
}

bool ColorPickerView::serialize( GB::VariantMap& ) const
{
    return false;
}

