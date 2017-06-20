//
//  BuilderToolBox.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "BuilderToolBox.hpp"
#include "BuilderMainView.hpp"

BuilderToolBox::BuilderToolBox( BuilderMainView* mainView):
_mainView(mainView)
{
    setOpaque(false);
    background = GXColors::DarkGray;
    
    
    _bttonSave.setBounds(GXRectMake(10, 10, 60, 20));
    _bttonSave.setText("Save");
    _bttonSave.onClic = std::bind(&BuilderMainView::actionSave, _mainView , std::placeholders::_1);
    addChild(&_bttonSave);
    
    _bttonLoad.setBounds(GXRectMake(80, 10, 60, 20));
    _bttonLoad.setText("Load");
    _bttonLoad.onClic = std::bind(&BuilderMainView::actionLoad, _mainView , std::placeholders::_1);
    addChild(&_bttonLoad);
    
    
    _itemsDropBown.setBounds(GXRectMake(10, 40, 60, 20));
    _itemsDropBown.setItems({ "Button" , "Label" , "Image" , "TextInput" , "slider"});
    _itemsDropBown.selectionDidChange = [this](VKSender* obj)
    {
        const VKDropDown* dp = dynamic_cast<const VKDropDown*>(obj);
        assert(dp);
        
        switch (dp->getSelectedIndex())
        {
            case 0:
                _mainView->addButton();
                break;
                
            case 1:
                _mainView->addLabel();
                break;
            case 2:
                _mainView->addImage();
                break;
            case 3:
                _mainView->addTextInput();
                break;
                
            case 4:
                _mainView->addSlider();
                break;
                
            default:
                break;
        }
        
    };
    
    addChild(&_itemsDropBown);
    
    

    
    
    _text.setSingleLine(true);
    _text.setBounds(GXRectMake(10, 70, 80, 30));
    _text.editingEnded = std::bind(&BuilderMainView::textContentChanged , _mainView , std::placeholders::_1);
    addChild(&_text);
    
    _inWidth.setSingleLine(true);
    _inWidth.setBounds(GXRectMake(10, 110, 80, 30));
    _inWidth.editingEnded = std::bind(&BuilderMainView::widthContentChanged , _mainView , std::placeholders::_1);
    addChild(&_inWidth);
    
    _inHeight.setSingleLine(true);
    _inHeight.setBounds(GXRectMake(100, 80, 80, 30));
    _inHeight.editingEnded = std::bind(&BuilderMainView::heightContentChanged , _mainView , std::placeholders::_1);
    addChild(&_inHeight);
}

void BuilderToolBox::paint( GXContext* context , const GXRect& bounds)
{
    context->addRoundedRect(bounds, 5);
    context->setFillColor(background);
    context->setStrokeColor(GXColors::White);
    context->fill();
    context->stroke();
}

bool BuilderToolBox::serialize( GB::VariantMap& obj) const
{
    return false;
}
