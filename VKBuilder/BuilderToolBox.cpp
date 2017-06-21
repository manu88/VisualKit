//
//  BuilderToolBox.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKStoryboard.hpp"
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
    
    /*
    _itemsDropBown.setBounds(GXRectMake(10, 40, 60, 20));
    _itemsDropBown.setItems({ "Button" , "Label" , "Image" , "TextInput" , "slider" , "dropDown" , "checkBox"});
    
    _itemsDropBown.selectionDidChange = [this](VKSender* obj)
    {

        
        _mainView->addItemAction(obj);
        
        
    };
    
    addChild(&_itemsDropBown);
    */
    
    _inView.setBounds(GXRectMake(5, 80, 250, 400));
    VKStoryboard::createFromFile(&_inView, "InspectorView.xml" , this);
    addChild(&_inView);
}

void BuilderToolBox::updateSelected( VKView* selected)
{
    assert(selected);
    
    VKTextInput* textW = dynamic_cast<VKTextInput*>( _inView.getChildByIdentifier("widthText") );
    assert(textW);
    textW->setContent( std::to_string( selected->getSize().width));
    
    
    //heightText
    VKTextInput* textH = dynamic_cast<VKTextInput*>( _inView.getChildByIdentifier("heightText") );
    assert(textH);
    textH->setContent( std::to_string( selected->getSize().height));
    
    VKTextInput* textID = dynamic_cast<VKTextInput*>( _inView.getChildByIdentifier("idText") );
    assert(textID);
    textID->setContent( selected->identifier);
    
    VKTextInput* textZ = dynamic_cast<VKTextInput*>( _inView.getChildByIdentifier("zText") );
    assert( textZ );
    textZ->setContent( std::to_string( selected->getZPos() ) );
    
    
    VKTextInput* textSRC = dynamic_cast<VKTextInput*>( _inView.getChildByIdentifier("srcText") );
    assert(textSRC);
    
    if( const VKButton* vt = dynamic_cast<const VKButton*>(selected))
    {
        textSRC->setContent(vt->getText());
    }
    else if( const VKLabel* lbl = dynamic_cast<const VKLabel*>(selected))
    {
        textSRC->setContent(lbl->getContent());
    }
    else if( const VKDropDown* dp = dynamic_cast<const VKDropDown*>(selected))
    {
        std::string str;
        for( const auto &item :dp->getItems())
        {
            str+= item +";";
        }
        
        textSRC->setContent(str);
    }
    
    
    textW->setNeedsRedraw();
    textH->setNeedsRedraw();
    textID->setNeedsRedraw();
    textSRC->setNeedsRedraw();
    textZ->setNeedsRedraw();
    
}

void BuilderToolBox::paint( GXContext* context , const GXRect& bounds)
{
    context->addRoundedRect(bounds, 5);
    context->setFillColor(background);
    context->setStrokeColor(GXColors::White);
    context->fill();
    context->stroke();
}

bool BuilderToolBox::serialize( GB::VariantMap& ) const
{
    return false;
}


void BuilderToolBox::onStoryboardAction(VKSender* sender)
{
    assert(sender);
    
    VKView* baseView = dynamic_cast< VKView* >(sender);
    
    if( baseView->identifier == "idText" )
    {
        VKTextInput* view = dynamic_cast<VKTextInput* >(baseView);
        
        //printf("Action from '%s' \n" , view->identifier.c_str());
        _mainView->setIdentifier(view->getContent());
        
    }
    else if( baseView->identifier == "widthText" )
    {
        VKTextInput* view = dynamic_cast<VKTextInput* >(baseView);
        _mainView->widthContentChanged( std::stoi(view->getContent()));

        
    }
    else if( baseView->identifier == "heightText" )
    {
        const VKTextInput* view = dynamic_cast<VKTextInput* >(baseView);
        _mainView->heightContentChanged( std::stoi(view->getContent()));

    }
    else if( baseView->identifier == "opaqueCheck")
    {
        if( _mainView->_selected)
        {
            const VKCheckBox* check = dynamic_cast< const VKCheckBox* >(baseView);
            _mainView->_selected->setOpaque(check->getState());
        }
    }
    else if( baseView->identifier == "singleLineCheck")
    {
        if( _mainView->_selected)
        {
            const VKCheckBox* check = dynamic_cast< const VKCheckBox* >(baseView);
            
            if( VKTextInput* textLine = dynamic_cast<VKTextInput*>(_mainView->_selected))
            {
                textLine->setSingleLine(check->getState());
            }
        }
    }
    else if( baseView->identifier == "srcText")
    {
        const VKTextInput* view = dynamic_cast<VKTextInput* >(baseView);
        _mainView->textContentChanged( view->getContent());
    }
    else if( baseView->identifier == "addWidget")
    {
        _mainView->addItemAction(sender);
    }
    else if( baseView->identifier == "zText")
    {
        const VKTextInput* view = dynamic_cast<VKTextInput* >(baseView);
        _mainView->zPosChanged(std::stoi(view->getContent()));
    }
    else
    {
        
        assert(baseView);
        
        printf("Unkown Action from '%s' \n" , baseView->identifier.c_str());
        //singleLineCheck
    }
}
