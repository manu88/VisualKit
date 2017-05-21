//
//  VKAlertView.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKAlertView_hpp
#define VKAlertView_hpp

#include "VKView.hpp"

#include "VKButton.hpp"

#include <functional>

class VKAlertView : public VKView
{
public:
    
    typedef std::function<void( VKAlertView*, int)> VKAlertViewDidReturn;
    
    VKAlertView();
    
    void setTitle( const std::string &t) noexcept
    {
        _title = t;
    }
    
    void setContent( const std::string &t) noexcept
    {
        _content = t;
    }
    
    VKAlertViewDidReturn onReturn;
    
protected:
    void buttonClicked( VKButton* button);
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool keyPressed(  const GXKey &key ) override;
    
    /*
    bool touchBegan( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    */
    
    
private:
    std::string _title;
    std::string _content;
    VKButton bttonOk;
    VKButton bttonCancel;

};

#endif /* VKAlertView_hpp */
