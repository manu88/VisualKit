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

class CustomView2;

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
    
    bool touchBegan( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    bool keyPressed(  const GXKey &key ) override;

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
    
    CustomView2* _view2;
    
};


#endif /* CustomView_hpp */
