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
    _view2 = nullptr;
    identifier = "CustomView";
    background = GXColors::LightGray;
    
    
    bttonOk.setText("Show");
    bttonOk.setSize( GXSizeMake( 60, 20));
    

    bttonCancel.setText("Close");
    bttonCancel.setSize( GXSizeMake( 60, 20));
    
    
    bttonNav.setText("Next");
    bttonNav.setSize( GXSizeMake( 60, 20));
    
    
    bttonNav.onClic = [this](VKSender* )
    {
        if (!_view2)
            _view2 = new CustomView2();
        
        CLApplication::instance()->pushView( _view2);
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
    
    
    _dropDown.setItems({ "red" , "green" , "blue"});
    _dropDown.selectionDidChange = std::bind(&CustomView::dropDownDidChange, this , std::placeholders::_1);
    
    _dropDown.setSize(GXSizeMake(100, 20));
    
    _alignDropDown.setSize(GXSizeMake(100, 20));
    _alignDropDown.setItems({ "Left" , "Center" , "Right"});
    
    optionsLayout.addChild(&_dropDown);
    optionsLayout.addChild(&_alignDropDown);
    textLayout.addChild( &optionsLayout);
    
    
    textLayout.addChild(&slider2);
    textLayout.addChild(&slider1);
    
    textLayout.addChild( &textInput);
    textLayout.addChild( &textInput2);

    slider1.setSize(GXSizeMake(200, 30));
    
    
    slider2.setSize(GXSizeMake(200, 30));
    
    addChild( &textLayout);
    
    slider2.valueDidChange = [this](VKSender* slider)
    {
        assert(slider == &slider2);
        
        slider1.setPosition(slider2.getPosition());
        slider1.setNeedsRedraw();
        
        textInput.setTextSize(VKDefaults::DefautFontSize*slider2.getPosition()*5);
        textInput.setNeedsRedraw();
    };
    
    slider1.identifier = "slider1";
    slider2.identifier = "slider2";
    
    textInput.identifier = "text1";
    textInput2.identifier = "text2";
    
    textInput.setContent("During the last decade, Unmanned Air Vehicles (UAVs) have replaced piloted aircraft in a broad band of missions, showing a high potential for further growing, especially due to the avoidance of human risk in dangerous environments. Typical present and future roles include weather reconnaissance, offshore and border patrol, search and rescue assisting operations in sea and mountains, aerial photographing and mapping, fire detection and coordination of fire fighting, traffic control etc. Advances in telecommunications, control and Artificial Intelligence along with UAV low risk, low cost and long endurance, tailor such missions to the UAV's profile.\n\tAutonomous operation of UAVs requires the development of control systems that operate isolated from human support for extended time periods. The development of such systems has been traditionally focused on ground vehicles. Additionally, the high cost and risk of testing air vehicles necessitates the use of sophisticated analysis and simulation tools.\n\tThe desired autonomous operations of UAVs leads to the development of pathline planners, for generating collision free paths in environments with obstacles. Such planners should work either on-board, for local real-time optimization of the flight path, or out-board, for global optimization of the mission, prior to the flight. The optimization of the flight path is, in general, a constrained multi-objective optimization problem. Additionally, a trajectory tracker is needed, in order to schedule the movement of the UAV along the optimized planned path.");
    
    textInput2.setContent(textInput.getContent());
    
    /*
    GB::Timer *t = new GB::Timer;
    t->setInterval(20);
    t->setCallback([this](const GB::Timer& )
    {
        float p = slider2.getPosition() + 0.01;
        if( p> 1.)
            p = 0;
        slider2.setPosition(p);
        slider2.setNeedsRedraw();
        
    });
    
    CLApplication::instance()->getRunLoop()->addSource(*t);
    */
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
    
//    printf("Selected : %zi \n" , _dropDown.getSelectedIndex() );
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
    
    textInput.setNeedsRedraw();
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
/*
void CustomView::paint( GXContext* context , const GXRect& bounds)
{

    const GXFontHandle font = context->getFontManager().getFont(VKDefaults::DefaultFont);// context->createFont(  VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );

    context->setFillColor(GXColors::Black);
    
    
    context->addTextBox(GXPointMake(bounds.size.width /2 , 20), 100, _test);

}
*/
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
