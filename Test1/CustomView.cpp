//
//  CustomView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CustomView.hpp"
#include "VK.hpp"
#include "CLApplication.hpp"


#include "CustomView2.hpp"
CustomView::CustomView():
buttonLayout(VKLayout::Horizontal),
textLayout(VKLayout::Vertical)
{
    background = GXColors::LightGray;
    
    
    bttonOk.setText("Show");
    bttonOk.setSize( GXSizeMake( 60, 20));
    

    bttonCancel.setText("Close");
    bttonCancel.setSize( GXSizeMake( 60, 20));
    
    
    bttonNav.setText("Next");
    bttonNav.setSize( GXSizeMake( 60, 20));
    
    
    bttonNav.onClic = [](VKSender* sender)
    {
        CLApplication::instance()->pushView(new CustomView2());
    };
    
    bttonOk.onClic = std::bind(&CustomView::buttonClicked,  this , std::placeholders::_1);
    bttonCancel.onClic = std::bind(&CustomView::buttonClicked, this , std::placeholders::_1);
    
    
    alert = nullptr;
    
    textInput.setSize(GXSizeMake(400, 200));
    textInput2.setSize(GXSizeMake(400, 200));
    

    buttonLayout.setPos(GXPointMake(10, 10));

    
    buttonLayout.addChild( &bttonNav );
    buttonLayout.addChild( &bttonOk );
    buttonLayout.addChild( &bttonCancel );
    
    
    textLayout.setPos(GXPointMake(20, 80));
    textLayout.addChild( &buttonLayout);
    textLayout.addChild( &_dropDown);
    textLayout.addChild( &textInput);
    textLayout.addChild( &textInput2);
    
    _dropDown.setItems({ "red" , "green" , "blue"});
    _dropDown.selectionDidChange = std::bind(&CustomView::dropDownDidChange, this , std::placeholders::_1);
    
    _dropDown.setSize(GXSizeMake(100, 20));
    
    
    slider1.setSize(GXSizeMake(200, 30));
    textLayout.addChild(&slider1);
    
    slider2.setSize(GXSizeMake(200, 30));
    textLayout.addChild(&slider2);
    
    addChild( &textLayout);
    
    slider2.valueDidChange = [this](VKSender* slider)
    {
        assert(slider == &slider2);
        
        slider1.setPosition(slider2.getPosition());
        slider1.setNeedsDisplay();
    };
    
}


void CustomView::viewWillAppear()
{
    CLApplication::instance()->setName("View 1");
}
void CustomView::viewDidDismiss()
{
    
}

void CustomView::dropDownDidChange( VKSender* sender)
{
    assert(sender == &_dropDown);
    
    printf("Selected : %zi \n" , _dropDown.getSelectedIndex() );
    if( _dropDown.getSelectedIndex() == 0)
    {
        textInput.setTextColor(GXColors::Red);
    }
    else if( _dropDown.getSelectedIndex() == 1)
    {
        textInput.setTextColor(GXColors::Green);
    }
    else if( _dropDown.getSelectedIndex() == 2)
    {
        textInput.setTextColor(GXColors::Blue);
    }
    
    textInput.setNeedsDisplay();
}

void CustomView::buttonClicked( VKSender* button)
{
    if( button == &bttonOk)
    {
        if( !alert)
        {
            alert = new VKAlertView();
            alert->setTitle("Hello");
            
            
            CLApplication::instance()->pushView(alert);
            alert->onReturn = [ this ]( VKAlertView* _alert , int code)
            {
                assert(_alert == alert);
                printf("Alert returned with code %i\n" , code);
                CLApplication::instance()->dismissView();
                delete alert;
                alert = nullptr;
            };
            //addChild( alert);
        }
    }
    else if( button == &bttonCancel)
    {
        CLApplication::instance()->quit();
    }
}

void CustomView::paint( GXContext* context , const GXRect& bounds)
{

    const GXFontHandle font = context->getFontManager().getFont(VKDefaults::DefaultFont);// context->createFont(  VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );

    context->setFillColor(GXColors::Black);
    
    
    context->addTextBox(GXPointMake(bounds.size.width /2 , 20), 100, _test);

}

bool CustomView::handleFocus() 
{
    return true;
}

void CustomView::focusChanged()
{
    printf("Focus changed to %i \n" , hasFocus());
}

bool CustomView::keyPressed(  const GXKey &key )
{
    if( hasFocus())
    {
        if(key.key == GXKey_UP)
        {
            printf("Key UP \n");
        }
        
        return true;
    }
    
    return VKView::keyPressed(key);
}



bool CustomView::touchBegan( const GXTouch &t)
{    
    return VKView::touchBegan(t);
}
bool CustomView::touchMoved( const GXTouch &t)
{
    
    return VKView::touchMoved(t);
}

bool CustomView::touchEnded( const GXTouch &t)
{
    return VKView::touchEnded(t);
}
