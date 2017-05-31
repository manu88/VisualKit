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
    
    bool handleFocus() override
    {
        return true;
    }
    
    void focusChanged() override;
    
    void viewWillAppear() override;
    void viewDidDismiss() override;
    
    void buttonClicked( VKSender* button);
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool touchBegan( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    bool keyPressed(  const GXKey &key ) override;
    
    std::string _test;
    
    VKLayout buttonLayout;
    VKButton bttonOk;
    VKButton bttonCancel;
    VKButton bttonNav;
    
    VKAlertView *alert;
    
    VKLayout textLayout;
    VKTextInput textInput;
    VKTextInput textInput2;
    
};


#endif /* CustomView_hpp */
