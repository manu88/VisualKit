//
//  BuilderToolBox.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef BuilderToolBox_hpp
#define BuilderToolBox_hpp

#include "VKButton.hpp"
#include "VKTextInput.hpp"
#include "VKView.hpp"
#include "ColorPickerView.hpp"

class BuilderMainView;
class BuilderToolBox : public VKView
{
public:
    BuilderToolBox(BuilderMainView* mainView);
    

    void paint( GXContext* context , const GXRect& bounds) override;
    bool serialize( GB::VariantMap& obj) const override;
    
    VKButton _bttonSave;
    VKButton _bttonLoad;
    VKButton _bttonAddButton;
    VKButton _bttonAddLabel;
    VKButton _bttonAddImg;
    VKTextInput _text;
    
    VKTextInput _inWidth;
    VKTextInput _inHeight;
    BuilderMainView* _mainView;
};

#endif /* BuilderToolBox_hpp */
