//
//  VKBuilderMainView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>
#include <GBXMLDocument.hpp>
#include "BuilderMainView.hpp"
#include "BuilderToolBox.hpp"

BuilderMainView::BuilderMainView():
_selected(nullptr),
_movingV( nullptr )
{
    background = GXColorMake( 0.96f ,0.96f ,0.96f);
    
    _toolBox = new BuilderToolBox( this);
    _toolBox->setBounds(GXRectMake(0, 0, 300, 400));
    addChild(_toolBox);
    
    /*
    _label.setBounds(GXRectMake(300, 500, 200, 100));
    _label.setContent("Hello world!");
    addChild(&_label);
    */
    
    
    
}

void BuilderMainView::viewWillAppear()
{
    //loadFile("test.xml");
    
    _colorView = new ColorPickerView(this);
    
    _colorView->setBounds(GXRectMake(220, 220, 250, 200));
    _colorView->setZPos(50);
    addChild( _colorView );
}

bool BuilderMainView::loadFile( const std::string &file)
{
    
    for( GXLayer* c : getChildren())
    {
        if( c != _toolBox && c != _colorView)
        {
            removeChild(c);
        }
    }
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
                
                const std::string type = cDesc.at("Type").toString();
                
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
                    ret = createTextInput(cDesc);
                }
                
                if( ret)
                {
                    addChild(ret);
                }
            }
        }
        
        
    }
    
    return false;
}

bool BuilderMainView::createBase(VKView* v , const GB::VariantMap &desc)
{
    assert(!desc.empty());
    
    if( !v)
        return false;
    
    const GB::VariantList _bounds = desc.at("Bounds").getList();
    assert(_bounds.size() == 4);

    v->setBounds(GXRectMake(_bounds.at(0).getInt(), _bounds.at(1).getInt(), _bounds.at(2).getInt(), _bounds.at(3).getInt()));
    
    return true;
}

VKView* BuilderMainView::createImage( const GB::VariantMap &desc)
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
VKView* BuilderMainView::createLabel( const GB::VariantMap &desc)
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
VKView* BuilderMainView::createButton( const GB::VariantMap &desc)
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

VKView* BuilderMainView::createTextInput( const GB::VariantMap &desc)
{
    if( desc.empty())
        return nullptr;
    
    VKTextInput* item = new VKTextInput();
    
    if( createBase(item, desc))
    {
        return item;
    }
    return nullptr;
}

void BuilderMainView::actionLoad( VKSender* )
{
    loadFile("test.xml");
}

void BuilderMainView::actionSave( VKSender* )
{
    printf("Save\n");
    
    GB::XMLDocument doc;
    GB::VariantMap obj;
    
    if(serialize(obj))
    {
        doc.addValueForKey(obj, "rootView");
        
        if( doc.save("test.xml"))
        {
            printf("Serialization ok\n");
        }
        else
        {
            printf("Error saving XML\n");
        }
    }
}

void BuilderMainView::addButton()
{
    VKButton* item = new VKButton;
    
    addItem(item);
    
}

void BuilderMainView::addLabel()
{
    VKLabel* item = new VKLabel;
    
    addItem(item);
}

void BuilderMainView::addImage()
{
    VKImage* item = new VKImage;
    
    addItem(item);
}

void BuilderMainView::addTextInput()
{
    VKTextInput* item = new VKTextInput;
    
    addItem(item);
    
}

bool BuilderMainView::addItem(VKView* item)
{
    assert( item );
    
    item->setSize(GXSizeMake(90, 50));
    item->setCenter(getCenter());
    
    return addChild(item);
}

bool BuilderMainView::touchBegan( const GXTouch &t)
{   
    for( GXLayer *c : getChildren())
    {
        VKView* subV = dynamic_cast<VKView*>(c);
        if( subV == _toolBox || subV == _colorView)
            continue;
        
        if( subV && rectContainsPoint(subV->getBounds(), t.center))
        {
            _selected = subV;
            itemSelectionChanged();
            break;
        }
    }
    return VKView::touchBegan(t);
}

bool BuilderMainView::touchMoved( const GXTouch &t)
{
    if( !_movingV)
    {
        for (GXLayer* l : getChildren())
        {
            VKView* view  = dynamic_cast<VKView*>(l);
            
            if( view)
            {
                if( rectContainsPoint(l->getBounds(), t.center))
                {
                    _movingV = view;
                    
                }
            }
        }
    }
    if( _movingV)
    {
        _movingV->setCenter(t.center);
    }

    
    return VKView::touchMoved(t);
}

bool BuilderMainView::touchEnded( const GXTouch &t)
{
    if( _movingV)
    {
        _movingV = nullptr;
        
    }
    
    return VKView::touchEnded(t);
}

void BuilderMainView::itemSelectionChanged()
{
    
    if( VKButton* bt = dynamic_cast<VKButton*>(_selected))
    {
        _toolBox->_text.setContent(bt->getText());
        
        
    }
    else if( VKImage* img = dynamic_cast<VKImage*>(_selected))
    {
        _toolBox->_text.setContent( img->getFile());
    }
    else if( VKLabel* lbl = dynamic_cast<VKLabel*>(_selected))
    {
        _toolBox->_text.setContent( lbl->getContent());
    }
    
    _toolBox->_text.setNeedsRedraw();
    
    _toolBox->_inWidth.setContent( std::to_string(_selected->getSize().width));
    _toolBox->_inHeight.setContent( std::to_string(_selected->getSize().height));
    
    _toolBox->_inHeight.setNeedsRedraw();
    _toolBox->_inWidth.setNeedsRedraw();

    _colorView->setColor(_selected->background);
    
}

void BuilderMainView::widthContentChanged( VKSender* sender)
{
    if( _selected)
    {
        const int newW = std::stoi( _toolBox->_inWidth.getContent());
        printf("new width %i\n" , newW);
        _selected->setSize(GXSizeMake( newW, _selected->getSize().height) );
        
        _selected->setNeedsDisplay();
    }
}

void BuilderMainView::heightContentChanged( VKSender* sender)
{
    if( _selected)
    {
        const int newH = std::stoi( _toolBox->_inHeight.getContent());
        printf("new height %i\n" , newH);
        _selected->setSize(GXSizeMake( _selected->getSize().width,newH ));
        _selected->setNeedsDisplay();
    }
}

void BuilderMainView::textContentChanged( VKSender* sender)
{
    if( sender == &_toolBox->_text)
    {
        if( _selected)
        {
            
            if( VKButton* bt = dynamic_cast<VKButton*>(_selected) )
            {
                bt->setText(_toolBox->_text.getContent());
                bt->setNeedsRedraw();
                
                return;
            }
            else if( VKImage* img = dynamic_cast<VKImage*>(_selected))
            {
                img->setFile(_toolBox->_text.getContent());
                img->setNeedsRedraw();
            }
            else if( VKLabel* lbl = dynamic_cast<VKLabel*>(_selected))
            {
                lbl->setContent(_toolBox->_text.getContent());
                lbl->setNeedsRedraw();
            }
        }
    }
}

void BuilderMainView::colorEditEnded( const GXColor& col)
{
    _selected->background = col;
    _selected->setNeedsDisplay();
}

bool BuilderMainView::keyPressed(  const GXKey &key )
{
    if( _selected && key.key == GXKey_UP)
    {

        _selected->setPos( _selected->getPos() - GXPointMake(0, 5));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_DOWN)
    {
        
        _selected->setPos( _selected->getPos() + GXPointMake(0, 5));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_LEFT)
    {
        
        _selected->setPos( _selected->getPos() - GXPointMake(5, 0));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_RIGHT)
    {
        
        _selected->setPos( _selected->getPos() + GXPointMake(5, 0));
        _selected->setNeedsDisplay();
    }
    /*
    else if( _selected && key.key == GXKey_BACKSPACE)
    {
        removeChild(_selected);
        _selected = nullptr;
    }
     */
    
    return VKView::keyPressed(key);
}
