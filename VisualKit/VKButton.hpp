//
//  VKButton.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKButton_hpp
#define VKButton_hpp


#include "VKAction.hpp"
#include "../../GX/include/GXLayer.hpp"
#include "VKView.hpp"



class VKButton : public VKView , public VKSender
{
public:
    
    
    
    enum State
    {
        Inactive = 0,
        Highlighted = 1
    };
    
    VKButton();
    virtual ~VKButton();
    
    void setText( const std::string &t) noexcept;
    const std::string &getText() const noexcept
    {
        return _text;
    }
    
    VKAction::Action onClic;
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool touchBegan( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    bool serialize( GB::VariantMap& obj) const override;
private:
    
    bool _triggerAction;
    State _state;
    std::string _text;
};

#endif /* VKButton_hpp */
