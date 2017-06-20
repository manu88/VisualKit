//
//  VKCheckBox.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 20/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKCheckBox_hpp
#define VKCheckBox_hpp

#include "VKView.hpp"
#include "VKAction.hpp"

class VKCheckBox : public VKView , public VKSender
{
public:
    VKCheckBox();
    
    void setDefaultState( bool state)
    {
        _defaultState = state;
    }
    void setState( bool state);
    bool getState() const noexcept
    {
        return _state;
    }
    
    VKAction::Action stateChanged;
private:
    void paint( GXContext*  , const GXRect& ) override;
    bool touchEnded( const GXTouch &t) override;
    
    bool serialize( GB::VariantMap& obj) const override;
    bool _state;
    bool _defaultState;
};

#endif /* VKCheckBox_hpp */
