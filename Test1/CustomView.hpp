//
//  CustomView.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CustomView_hpp
#define CustomView_hpp

#include <GBRunLoopSource.hpp>
#include "VK.hpp"


class CustomView : public VKView
{
public:
    CustomView();

protected:
    
    bool handleFocus() override;
    
    void focusChanged() override;
    
    void viewWillAppear() override;
    void viewDidDismiss() override;
    
    void dropDownDidChange( VKSender* );
    void buttonClicked( VKSender* );
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool touchBegan( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    bool keyPressed(  const GXKey &key ) override;
    
    std::string _test;
    
    
    VKDropDown _dropDown;
    VKDropDown _alignDropDown;
    VKLayout optionsLayout;
    VKLayout buttonLayout;
    VKButton bttonOk;
    VKButton bttonCancel;
    VKButton bttonNav;
    
    VKAlertView *alert;
    
    VKLayout textLayout;
    VKTextInput textInput;
    VKTextInput textInput2;
    
    VKSlider slider1;
    VKSlider slider2;
    
};


#endif /* CustomView_hpp */
