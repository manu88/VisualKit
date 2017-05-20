//
//  VKTextInput.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKTextInput.hpp"
#include "VK.hpp"
#include "CLApplication.hpp"
#include "../../GX/src/nanovg/nanovg.h"

VKTextInput::VKTextInput()
{
    
    setOpaque(false);
    
    _block.setBounds(GXRectMake(10, 10, 7, 15));
    _block.background = GXColorMake(0, 1., 0.35);
    
    
    
    tBlock.setInterval(800);
    tBlock.setCallback([this](GB::Timer &timer)
    {
        
        _block.setVisible( !_block.isVisible());
        _block.setNeedsDisplay();
    });
    
    _content = "Les Iraniens ont voté massivement, vendredi 19 mai, pour reconduire le modéré Hassan Rohani à la présidence pendant quatre ans. Il a obtenu, dès le premier tour, la majorité absolue avec une confortable avance : 57 % des voix, selon les résultats officiels communiqués en fin de matinée par le ministère de l’intérieur.";
}

void VKTextInput::focusChanged()
{
    if( hasFocus())
    {
        addChild(&_block);
        
        _block.setVisible(true);
        CLApplication::runLoop->addSource(tBlock);
        setNeedsDisplay();
    }
    else
    {
        removeChild(&_block);
        CLApplication::runLoop->removeSource(tBlock);
        setNeedsDisplay();
    }
}

bool VKTextInput::keyPressed(  const GXKey &key )
{
    std::string c = getContent();
    
    if( key.key == GXKey_BACKSPACE)
    {
        if( !c.empty())
        {
            c.pop_back();
        }
    }
    else if( key.key == GXKey_ENTER)
    {
        c.append("\n");
    }
    else
    {
        c.append( key.toStr() );
    }
    setContent(c);
    setNeedsDisplay();
    
    return true;
}

bool VKTextInput::touchBegan( const GXTouch &t)
{
    _cursorPos = t.center;
    return VKView::touchBegan(t);
}

void VKTextInput::paint( GXContext* context , const GXRect& bounds)
{
    context->addRoundedRect(bounds, 5);
    context->setFillColor(GXColors::White);
    context->setStrokeColor( GXColors::Black);
    context->fill();
    context->stroke();
    context->setFontSize(20);
    context->setFontId( context->getFontManager().getFont( VKDefaults::DefaultFont) );
    context->setFillColor( GXColors::Black);// GXColorMake(0, 1., 0.35) );
    context->setTextAlignement(GXTextAlign_LEFT | GXTextAlign_TOP);
    
    const GXPoint textPos = GXPointMake(5, 10);
    
    //context->addTextBox(textPos, bounds.size.width, _content);
    
    const char* c = _content.c_str();
    
    NVGtextRow rows[3];
    int totalRows = 0;
    int nrows =0;
    const char* start = c;
    const char* end = c + strlen(c);
    
    float lineh;
    context->getTextMetrics(nullptr , nullptr , &lineh);
    
    int x = textPos.x;
    int y = textPos.y;
    
    int lnum = 0;
    
    float caretx;
    float px;
    int nglyphs = 0;
    NVGglyphPosition glyphs[100];
    
    while((nrows = context->textBreakLines( start, end, bounds.size.width, rows, 3)))
    {
        for (int i = 0; i < nrows; i++)
        {
            NVGtextRow* row = &rows[i];
            int hit = _cursorPos.x > x && _cursorPos.x < (x+bounds.size.width) && _cursorPos.y >= y && _cursorPos.y < (y+lineh);
            
            
            
            
            
            context->addText(GXPointMake(x, y), row->start, row->end);
            
            if (hit)
            {
                caretx = (_cursorPos.x < x+row->width/2) ? x : x+row->width;
                px = x;
                nglyphs = nvgTextGlyphPositions(static_cast<NVGcontext*>( context->getImpl() ),
                                                x, y, row->start, row->end, glyphs, 100);
                
                for (int j = 0; j < nglyphs; j++)
                {
                    float x0 = glyphs[j].x;
                    float x1 = (j+1 < nglyphs) ? glyphs[j+1].x : x+row->width;
                    float gx = x0 * 0.3f + x1 * 0.7f;
                    if (_cursorPos.x >= px && _cursorPos.x < gx)
                        caretx = glyphs[j].x;
                    px = gx;
                }
                _block.setPos(GXPointMake(caretx, y));
                /*
                context->beginPath();
                nvgFillColor(static_cast<NVGcontext*>( context->getImpl() ), nvgRGBA(255,192,0,255));
                nvgRect(static_cast<NVGcontext*>( context->getImpl() ), caretx, y, 1, lineh);
                nvgFill(static_cast<NVGcontext*>( context->getImpl() ));
                */
                /*
                gutter = lnum+1;
                gx = x - 10;
                gy = y + lineh/2;
                 */
            }
            
            lnum++;
            y += lineh;
        }
        
        totalRows += nrows;
        start = rows[nrows-1].next;
    }
    
    printf("Rows : %i\n" , totalRows );
    
}
