//
//  VKStoryboard.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 20/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <GBXMLDocument.hpp>
#include <stdio.h>
#include <iostream>
#include "VK.hpp"
#include "VKStoryboard.hpp"


static bool createBase(VKView* v , const GB::VariantMap &desc);
static VKView* createImage( const GB::VariantMap &desc);
static VKView* createLabel( const GB::VariantMap &desc);
static VKView* createButton( const GB::VariantMap &desc);

static VKView* createTextInput( const GB::VariantMap &desc , VKStoryboardController* controller);
static VKView* createCheckBox( const GB::VariantMap &desc , VKStoryboardController* controller);
static VKView* createSlider( const GB::VariantMap &desc);

static bool createBase(VKView* v , const GB::VariantMap &desc)
{
    assert(!desc.empty());
    
    if( !v)
        return false;
    
    const GB::VariantList _bounds = desc.at("Bounds").getList();
    assert(_bounds.size() == 4);
    
    if( desc.count("Identifier"))
    {
        v->identifier = desc.at("Identifier").getString();
    }
    
    
    
    /*
    if( desc.count("Opaque"))
    {
        v->setOpaque(desc.at("Opaque").getInt());
    }
     */
    v->setBounds(GXRectMake(_bounds.at(0).getInt(), _bounds.at(1).getInt(), _bounds.at(2).getInt(), _bounds.at(3).getInt()));
    
    return true;
}

static VKView* createImage( const GB::VariantMap &desc)
{
    if( desc.empty())
        return nullptr;
    
    VKImage* img = new VKImage();
    
    if( createBase(img, desc))
    {
        img->setFile( desc.at("Res").getString());
        return img;
    }
    
    return nullptr;
}
static VKView* createLabel( const GB::VariantMap &desc)
{
    if( desc.empty())
        return nullptr;
    
    VKLabel* lbl = new VKLabel();
    
    
    if( createBase(lbl, desc))
    {
        lbl->setContent( desc.at("Res").getString() );
        return lbl;
    }
    
    return nullptr;
}
static VKView* createButton( const GB::VariantMap &desc)
{
    if( desc.empty())
        return nullptr;
    
    VKButton* bt = new VKButton();
    
    
    if( createBase(bt, desc))
    {
        bt->setText( desc.at("Text").getString() );
        return bt;
    }
    
    return nullptr;
}

static VKView* createCheckBox( const GB::VariantMap &desc , VKStoryboardController* controller)
{
    if( desc.empty())
        return nullptr;
    
    VKCheckBox* item  = new VKCheckBox();
    
    if( createBase(item, desc))
    {
        if( controller)
        {
            item->stateChanged = std::bind(&VKStoryboardController::onStoryboardAction, controller , std::placeholders::_1);
        }
        return item;
    }
    
    return nullptr;
}

static VKView* createTextInput( const GB::VariantMap &desc , VKStoryboardController* controller)
{
    if( desc.empty())
        return nullptr;
    
    VKTextInput* item = new VKTextInput();
    
    if( createBase(item, desc))
    {
        if( desc.count("SingleLine"))
        {
            item->setSingleLine( desc.at("SingleLine").toInt());
        }
        
        if( controller)
        {
            item->editingEnded = std::bind(&VKStoryboardController::onStoryboardAction, controller , std::placeholders::_1);
        }
        return item;
    }
    return nullptr;
}

static VKView* createSlider( const GB::VariantMap &desc)
{
    if( desc.empty())
        return nullptr;
    
    VKSlider* item = new VKSlider();
    
    if( createBase(item, desc))
    {
        return item;
    }
    return nullptr;
}

/*static*/ bool VKStoryboard::createFromFile(VKView* view , const std::string &file , VKStoryboardController* controller)
{
    
    assert(view);
    
    GB::XMLDocument doc(file);
    
    printf("Num elements %zi \n" , doc.getSize());
    if(doc.contains("rootView"))
    {
        const GB::VariantMap rootView = doc.getValueForKey("rootView").getMap();
        
        if( rootView.count("Children"))
        {
            const GB::VariantList children = rootView.at("Children").getList();
            
            for( const GB::Variant &c : children)
            {
                const GB::VariantMap cDesc = c.getMap();
                
                const std::string type = cDesc.at("Class").toString();
                
                std::cout << "Got 1 child type " << type << "\n";
                
                VKView* ret = nullptr;
                
                if( type == "VKButton")
                {
                    ret = createButton(cDesc);
                }
                else if( type == "VKImage")
                {
                    ret = createImage(cDesc);
                }
                else if( type == "VKLabel")
                {
                    ret = createLabel(cDesc);
                }
                else if( type == "VKTextInput")
                {
                    ret = createTextInput(cDesc , controller);
                }
                else if( type == "VKSlider")
                {
                    ret = createSlider(cDesc);
                }
                else if( type == "VKCheckBox")
                {
                    ret = createCheckBox(cDesc , controller);
                }
                else
                {
                    assert(false);
                }
                if( ret)
                {
                    view->addChild(ret);
                }
            } // end for children loop
        }
        
        return true;
    }
    
    return false;

    
}
