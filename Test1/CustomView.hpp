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
#include "VKView.hpp"
#include "VKButton.hpp"
#include "VKAlertView.hpp"
#include "VKTextInput.hpp"

#include "VKKeyboard.hpp"

class CustomView : public VKView
{
public:
    CustomView();

protected:
    
    
    void viewWillAppear() override;
    void viewDidDismiss() override;
    
    void buttonClicked( VKSender* button);
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool touchBegan( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    
    
    std::string _test;
    
    VKButton bttonOk;
    VKButton bttonCancel;
    VKButton bttonNav;
    
    VKAlertView *alert;
    
    
    VKTextInput textInput;
    VKTextInput textInput2;
    
};


#endif /* CustomView_hpp */
