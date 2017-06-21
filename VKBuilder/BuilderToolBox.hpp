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
#include "VKDropDown.hpp"
#include "ColorPickerView.hpp"
#include "VKStoryboard.hpp"

class BuilderMainView;
class BuilderToolBox : public VKView , public VKStoryboardController
{
public:
    BuilderToolBox(BuilderMainView* mainView);
    

    void paint( GXContext* context , const GXRect& bounds) override;
    bool serialize( GB::VariantMap& obj) const override;
    
    
    void updateSelected( VKView* selected);
    void onStoryboardAction(VKSender* sender) override;
    
//    VKDropDown _itemsDropBown;
    
    VKButton _bttonSave;
    VKButton _bttonLoad;
    

    
    VKView _inView;
    BuilderMainView* _mainView;
    
};

#endif /* BuilderToolBox_hpp */
