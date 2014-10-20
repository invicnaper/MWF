#include "cppw_rawimage.h"

#include "cppw_file.h"

#include <cstdlib>
#include <cmath>

void CWHSV::ToRGB(CWRGB* pRGB) const
{
    uint8_t region, remainder, p, q, t;

    if (Saturation == 0)
    {
        pRGB->Red = Value;
        pRGB->Green = Value;
        pRGB->Blue = Value;
        return;
    }

    region = Hue / 43;
    remainder = (Hue - (region * 43)) * 6;

    p = (Value * (255 - Saturation)) >> 8;
    q = (Value * (255 - ((Saturation * remainder) >> 8))) >> 8;
    t = (Value * (255 - ((Saturation * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            pRGB->Red = Value; pRGB->Green = t; pRGB->Blue = p;
            break;
        case 1:
            pRGB->Red = q; pRGB->Green = Value; pRGB->Blue = p;
            break;
        case 2:
            pRGB->Red = p; pRGB->Green = Value; pRGB->Blue = t;
            break;
        case 3:
            pRGB->Red = p; pRGB->Green = q; pRGB->Blue = Value;
            break;
        case 4:
            pRGB->Red = t; pRGB->Green = p; pRGB->Blue = Value;
            break;
        default:
            pRGB->Red = Value; pRGB->Green = p; pRGB->Blue = q;
            break;
    }
}

void CWRGB::ToHSV(CWHSV* pHSV) const
{
    uint8_t rgbMin, rgbMax;

    rgbMin = Red < Green ? (Red < Blue ? Red : Blue) : (Green < Blue ? Green : Blue);
    rgbMax = Red > Green ? (Red > Blue ? Red : Blue) : (Green > Blue ? Green : Blue);

    pHSV->Value = rgbMax;
    if (pHSV->Value == 0)
    {
        pHSV->Hue = 0;
        pHSV->Saturation = 0;
        return;
    }

    pHSV->Saturation = 255 * long(rgbMax - rgbMin) / pHSV->Value;
    if (pHSV->Saturation == 0)
    {
        pHSV->Hue = 0;
        return;
    }

    if (rgbMax == Red)
        pHSV->Hue = 0 + 43 * (Green - Blue) / (rgbMax - rgbMin);
    else if (rgbMax == Green)
        pHSV->Hue = 85 + 43 * (Blue - Red) / (rgbMax - rgbMin);
    else
        pHSV->Hue = 171 + 43 * (Red - Green) / (rgbMax - rgbMin);
}

// -----------------
// -----------------


CWHorzLine::CWHorzLine(int iStartX, int iEndX, int iY)
{
    StartX = iStartX;
    EndX = iEndX;

    Y = iY;
}

bool CWHorzLine::Contains(int iX, int iY) const
{
    return iY == Y && iX >= StartX && iX <= EndX;
}

bool CWHorzLine::Touches(int iX, int iY) const
{
    return (iY >= Y - 1 && iY <= Y + 1) && (iX >= StartX - 1 && iX <= EndX + 1);
}

bool CWHorzLine::Touches(CWHorzLine* pLine) const
{
    return Touches(pLine->StartX, pLine->Y) || Touches(pLine->EndX, pLine->Y);
}


// -----------------
// -----------------


CWSelection::CWSelection(bool bOwnsObjects)
{
    OwnsObjects = bOwnsObjects;

    Rect.Set();

    tmp = 0;
}

int CWSelection::Count() const
{
    return Items.size();
}

void CWSelection::Clear()
{
    if(OwnsObjects)
    {
        int count = Count();
        for(int i = 0; i < count; i++)
            delete Items[i];
    }
    Items.clear();
    GetRect(&Rect);
}

void CWSelection::Add(CWHorzLine* pLine)
{
    bool was_empty = Count() == 0;

    Items.push_back(pLine);

    if(was_empty)
        GetRect(&Rect);
    else
        Rect.Merge(pLine->StartX, pLine->Y, pLine->EndX, pLine->Y);
}

void CWSelection::Add(int iStartX, int iEndX, int iY)
{
    bool was_empty = Count() == 0;

    Add(new CWHorzLine(iStartX, iEndX, iY));

    if(was_empty)
        GetRect(&Rect);
    else
        Rect.Merge(iStartX, iY, iEndX, iY);
}

void CWSelection::Append(CWSelection* pSelection)
{
    bool was_empty = Count() == 0;

    int count = pSelection->Count();
    for(int i = 0; i < count; i++)
    {
        CWHorzLine* line = pSelection->Items[i];
        Add(line->StartX, line->EndX, line->Y);
    }

    if(was_empty)
        GetRect(&Rect);
    else
        Rect.Merge(&(pSelection->Rect));
}

void CWSelection::Delete(int iIndex)
{
    if(OwnsObjects) delete Items[iIndex];
    Items.erase(Items.begin() + iIndex);

    GetRect(&Rect);
}

bool CWSelection::Touches(CWHorzLine* pLine) const
{
    if(!Rect.Touches(pLine->StartX, pLine->Y, pLine->EndX, pLine->Y))
        return false;

    int count = Count();
    for(int i = 0; i < count; i++)
    {
        if(Items[i]->Touches(pLine))
            return true;
    }
    return false;
}

bool CWSelection::Touches(CWSelection* pSelection) const
{
    if(!Rect.Touches(&pSelection->Rect))
        return false;

    int count = Count();
    for(int i = 0; i < count; i++)
    {
        if(pSelection->Touches(Items[i]))
            return true;
    }
    return false;
}

void CWSelection::SplitIntoObjects(CWSelectionList* pList)
{
    pList->Clear();
    int count = Count();
    CWSelection* belongs_to = NULL;
    for(int i = 0; i < count; i++)
    {
        CWHorzLine* line = Items[i];

        if(belongs_to == NULL || !belongs_to->Touches(line))
            belongs_to = pList->FindTouchingSelection(line);

        if(belongs_to == NULL)
        {
            belongs_to = new CWSelection();
            pList->Add(belongs_to);
        }
        belongs_to->Add(line->StartX, line->EndX, line->Y);
    }

    pList->JoinTouchingSelections();
}

void CWSelection::GetRect(CWRect* pRect) const
{
    pRect->TopX = 0;
    pRect->TopY = 0;
    pRect->BottomX = 0;
    pRect->BottomY = 0;

    int count = Count();
    for(int i = 0; i < count; i++)
    {
        CWHorzLine* line = Items[i];

        if(i == 0)
        {
            pRect->TopX = line->StartX;
            pRect->TopY = line->Y;
            pRect->BottomX = line->EndX;
            pRect->BottomY = line->Y;
        }
        else
        {
            if(line->StartX < pRect->TopX) pRect->TopX = line->StartX;
            if(line->EndX > pRect->BottomX) pRect->BottomX = line->EndX;
            if(line->Y < pRect->TopY) pRect->TopY = line->Y;
            if(line->Y > pRect->BottomY) pRect->BottomY = line->Y;
        }
    }
}

// -----------------
// -----------------


CWSelectionList::CWSelectionList(bool bOwnsObjects)
{
    OwnsObjects = bOwnsObjects;
}

int CWSelectionList::Count() const
{
    return Items.size();
}

void CWSelectionList::Clear()
{
    if(OwnsObjects)
    {
        int count = Count();
        for(int i = 0; i < count; i++)
            delete Items[i];
    }
    Items.clear();
}

void CWSelectionList::Add(CWSelection* pSelection)
{
    Items.push_back(pSelection);
}

void CWSelectionList::Delete(int iIndex)
{
    if(OwnsObjects) delete Items[iIndex];
    Items.erase(Items.begin() + iIndex);
}

CWSelection* CWSelectionList::FindTouchingSelection(CWHorzLine* pLine) const
{
    int count = Count();
    for(int i = 0; i < count; i++)
    {
        if(Items[i]->Touches(pLine))
            return Items[i];
    }
    return NULL;
}

void CWSelectionList::JoinTouchingSelections(int iStartIndex)
{
    int count = Count();
    for(int i = iStartIndex; i < count; i++)
    {
        for(int x = count - 1; x >= 0; x--)
        {
            if(x != i)
            {
                if(Items[x]->Touches(Items[i]))
                {
                    Items[i]->Append(Items[x]);
                    Delete(x);
                    count--;
                    if(x < i)
                        i--;
                }
            }
        }
    }
}

void CWSelectionList::Swap(int iIndex1, int iIndex2)
{
    std::swap(Items[iIndex1], Items[iIndex2]);
}

void CWSelectionList::SortByArea(int iStart, int iEnd)
{
    int i = iStart;
    int k = iEnd;

    if(iEnd - iStart >= 1)
    {
        while(k > i)
        {
            while(Items[i]->tmp <= Items[iStart]->tmp && i <= iEnd && k > i)
                i++;
            while(Items[k]->tmp > Items[iStart]->tmp && k >= iStart && k >= i)
                k--;

            if(k > i)
            {
                if(Items[i]->tmp != Items[k]->tmp)
                    Swap(i, k);
            }
        }

        if(Items[iStart]->tmp != Items[k]->tmp)
            Swap(iStart, k);

        if(k > iStart)
            SortByArea(iStart, k - 1);
        if(k < iEnd)
            SortByArea(k + 1, iEnd);
    }
}

void CWSelectionList::SortByArea()
{
    int count = Count();
    for(int i = 0; i < count; i++)
        Items[i]->tmp = Items[i]->Rect.Area();

    SortByArea(0, Count() - 1);
}

// -----------------
// -----------------

CWRect::CWRect(int iTopX, int iTopY, int iBottomX, int iBottomY)
{
    Set(iTopX, iTopY, iBottomX, iBottomY);

    tmp = 0;
}

void CWRect::Set(int iTopX, int iTopY, int iBottomX, int iBottomY)
{
    TopX = iTopX;
    TopY = iTopY;
    BottomX = iBottomX;
    BottomY = iBottomY;
}

bool CWRect::Intersects(int iTopX, int iTopY, int iBottomX, int iBottomY) const
{
    return TopX <= iBottomX && BottomX >= iTopX && TopY <= iBottomY && BottomY >= iTopY;
}

bool CWRect::Intersects(CWRect* pRect) const
{
    return Intersects(pRect->TopX, pRect->TopY, pRect->BottomX, pRect->BottomY);
}

bool CWRect::Touches(int iTopX, int iTopY, int iBottomX, int iBottomY) const
{
    return TopX <= iBottomX + 1 && BottomX >= iTopX - 1 && TopY <= iBottomY + 1 && BottomY >= iTopY - 1;
}

bool CWRect::Touches(CWRect* pRect) const
{
    return Touches(pRect->TopX, pRect->TopY, pRect->BottomX, pRect->BottomY);
}

bool CWRect::Contains(int iX, int iY) const
{
    return iX >= TopX && iX <= BottomX && iY >= TopY && iY <= BottomY;
}

void CWRect::Merge(int iTopX, int iTopY, int iBottomX, int iBottomY, bool* pIsExpanded)
{
    if(pIsExpanded != NULL) *pIsExpanded = false;

    if(TopX > iTopX) { TopX = iTopX; if(pIsExpanded != NULL) *pIsExpanded = true; }
    if(BottomX < iBottomX) { BottomX = iBottomX; if(pIsExpanded != NULL) *pIsExpanded = true; }

    if(TopY > iTopY) { TopY = iTopY; if(pIsExpanded != NULL) *pIsExpanded = true; }
    if(BottomY < iBottomY) { BottomY = iBottomY; if(pIsExpanded != NULL) *pIsExpanded = true; }
}

void CWRect::Merge(CWRect* pRect, bool* pIsExpanded)
{
    Merge(pRect->TopX, pRect->TopY, pRect->BottomX, pRect->BottomY, pIsExpanded);
}

int CWRect::Width() const
{
    return (BottomX - TopX) + 1;
}

int CWRect::Height() const
{
    return (BottomY - TopY) + 1;
}

int CWRect::Area() const
{
    return Width() * Height();
}


// -----------------
// -----------------


CWRectList::CWRectList()
{

}

CWRectList::~CWRectList()
{
    Clear();
}

int CWRectList::Count()
{
    return Items.size();
}

void CWRectList::Clear()
{
    int count = Count();
    for(int i = 0; i < count; i++)
        delete Items[i];
    Items.clear();
}

void CWRectList::Add(CWRect* pRect)
{
    Items.push_back(pRect);
}

void CWRectList::Add(int iTopX, int iTopY, int iBottomX, int iBottomY)
{
    Add(new CWRect(iTopX, iTopY, iBottomX, iBottomY));
}

void CWRectList::Delete(int iIndex)
{
    delete Items[iIndex];
    Items.erase(Items.begin() + iIndex);
}

void CWRectList::Swap(int iIndex1, int iIndex2)
{
    std::swap(Items[iIndex1], Items[iIndex2]);
}

void CWRectList::SortByArea(int iStart, int iEnd)
{
    int i = iStart;
    int k = iEnd;

    if(iEnd - iStart >= 1)
    {
        while(k > i)
        {
            while(Items[i]->tmp <= Items[iStart]->tmp && i <= iEnd && k > i)
                i++;
            while(Items[k]->tmp > Items[iStart]->tmp && k >= iStart && k >= i)
                k--;

            if(k > i)
            {
                if(Items[i]->tmp != Items[k]->tmp)
                    Swap(i, k);
            }
        }

        if(Items[iStart]->tmp != Items[k]->tmp)
            Swap(iStart, k);

        if(k > iStart)
            SortByArea(iStart, k - 1);
        if(k < iEnd)
            SortByArea(k + 1, iEnd);
    }
}

void CWRectList::SortByArea()
{
    int count = Count();
    for(int i = 0; i < count; i++)
        Items[i]->tmp = Items[i]->Area();

    SortByArea(0, Count() - 1);
}

// -----------------
// -----------------


CWRawImage::CWRawImage()
{
    Buffer = NULL;
}

CWRawImage::~CWRawImage()
{
    Free();
}

void CWRawImage::Free()
{
    if(Buffer != NULL)
    {
        delete Buffer;
        Buffer = NULL;
    }
}

bool CWRawImage::LoadFromFile(string sFileName, uint32_t iWidth, uint32_t iHeight, uint8_t iPixelFormat, string* pErrorMessage)
{
    Free();

    uint8_t* buffer = NULL;
    uint32_t file_size = 0;
    if(!FileLoad(sFileName, (void**)&buffer, (int*)&file_size, 0, pErrorMessage))
        return false;

	uint32_t width = iWidth;
	uint32_t height = iHeight;
	uint8_t pixel_format = iPixelFormat;

    uint32_t buffpos = 0;
    if(file_size >= 12 && buffer[0] == 'J' && buffer[1] == 'B' && buffer[2] == 'G')
    {
        // has JBG header
        buffpos = 3;

        memcpy(&width, buffer + buffpos, sizeof(uint32_t)); buffpos += sizeof(uint32_t);
        memcpy(&height, buffer + buffpos, sizeof(uint32_t)); buffpos += sizeof(uint32_t);
        memcpy(&pixel_format, buffer + buffpos, sizeof(uint8_t)); buffpos += sizeof(uint8_t);
    }
	else
	{
		// nema header-a... da li velicina fajla odgovara rezoluciji?
		// ako je pixel format = 0 (24bit RGB888)
		if(file_size < (width * height * 3))
		{
			if(file_size < (width * height * 2))
			{
			    if(pErrorMessage != NULL) *pErrorMessage = "Invalid file size.";
			    free(buffer);
				return false;
			}
			else
				pixel_format = 1; // ako je fajl manji od w*h*3, a veci ili jednak w*h*2, pretpostavljamo da je 16bit RGB565
		}
	}

    Buffer = (uint8_t*)malloc(width * height * 3);
	if(Buffer == NULL)
	{
        if(pErrorMessage != NULL) *pErrorMessage = "Out of memory.";
        free(buffer);
		return false;
	}

    if(pixel_format == 0)
    {
        // already RGB888
        memcpy(Buffer, buffer + buffpos, width * height * 3);
    }
    else
    {
        if(pixel_format == 1)
        {
            // convert RGB565 to RGB888
            uint16_t color = 0;
            int pos = 0;
            while(buffpos < file_size)
            {
                memcpy(&color, buffer + buffpos, sizeof(uint16_t)); buffpos += sizeof(uint16_t);
                // 5-6-5 dekodiranje slike (5 bitova RED, 6 bitova GREEN, 5 bitova BLUE
                Buffer[pos] = ((color & 63488) >> 11) * 8; pos++;
                Buffer[pos] = ((color & 2016) >> 5) * 4; pos++;
                Buffer[pos] = (color & 31) * 8; pos++;
            }
        }
    }

    Width = width;
    Height = height;

    free(buffer);
    return true;
}

bool CWRawImage::SaveToFile(string sFileName, uint8_t iPixelFormat, bool bJBGHeader, string* pErrorMessage)
{
    int fd = -1;
    if(!FileCreate(sFileName, &fd, pErrorMessage))
        return false;

    if(bJBGHeader)
    {
        // write 12-byte JBG header
        uint8_t* header = (uint8_t*)malloc(12);
        uint32_t hpos = 0;
        memcpy(header + hpos, "JBG", 3); hpos += 3;
        memcpy(header + hpos, &Width, sizeof(uint32_t)); hpos += sizeof(uint32_t);
        memcpy(header + hpos, &Height, sizeof(uint32_t)); hpos += sizeof(uint32_t);
        memcpy(header + hpos, &iPixelFormat, sizeof(uint8_t)); hpos += sizeof(uint8_t);

        if(!FileWrite(fd, header, 12, pErrorMessage))
        {
            free(header);
            FileClose(fd, NULL);
            return false;
        }
        free(header);
    }

    if(iPixelFormat == 0)
    {
        // Write internal buffer (already RGB888)
        if(!FileWrite(fd, Buffer, Width * Height * 3, pErrorMessage))
        {
            FileClose(fd, NULL);
            return false;
        }
    }
    else
    {
        // Convert to RGB565
        int num_pixels = Width * Height;
        int data_size = num_pixels * 2;
        uint8_t* data = (uint8_t*)malloc(data_size);

        int data_counter = 0;
        int buffer_counter = 0;
        for(int i = 0; i < num_pixels; i++)
        {
            unsigned char R = Buffer[buffer_counter++];
            unsigned char G = Buffer[buffer_counter++];
            unsigned char B = Buffer[buffer_counter++];

            B = (B * 31) / 255;
            G = (G * 63) / 255;
            R = (R * 31) / 255;

            data[data_counter++] = B | ((G & 7) << 5);
            data[data_counter++] = ((G & 56) >> 3) | ((R & 31) << 3);
        }

        // Write internal buffer (already RGB888)
        if(!FileWrite(fd, data, data_size, pErrorMessage))
        {
            free(data);
            FileClose(fd, NULL);
            return false;
        }
        free(data);
    }

    FileClose(fd, NULL);
    return true;
}

void CWRawImage::GetPixelRGB(uint32_t iX, uint32_t iY, CWRGB* pRGB)
{
    int buffpos = (Width * (iY * 3)) + (iX * 3);

    pRGB->Red = Buffer[buffpos];
    pRGB->Green = Buffer[buffpos + 1];
    pRGB->Blue = Buffer[buffpos + 2];
}

void CWRawImage::SetPixelRGB(uint32_t iX, uint32_t iY, const CWRGB& RGB)
{
    int buffpos = (Width * (iY * 3)) + (iX * 3);

    Buffer[buffpos] = RGB.Red;
    Buffer[buffpos + 1] = RGB.Green;
    Buffer[buffpos + 2] = RGB.Blue;
}

bool CWRawImage::IsPixelSimilar(uint32_t iX, uint32_t iY, const CWHSV& HSVColor, uint8_t iTolerHue, uint8_t iTolerSaturation, uint8_t iTolerValue)
{
    // get pixel RGB
    CWRGB RGB;
    GetPixelRGB(iX, iY, &RGB);

    // convert to HSV
    CWHSV HSV;
    RGB.ToHSV(&HSV);

    return abs(HSV.Hue - HSVColor.Hue) <= iTolerHue && abs(HSV.Saturation - HSVColor.Saturation) <= iTolerSaturation && abs(HSV.Value - HSVColor.Value) <= iTolerValue;
}

void CWRawImage::SelectColor(const CWRect& Rect, const CWRGB& RGBColor, uint8_t iTolerHue, uint8_t iTolerSaturation, uint8_t iTolerValue, CWSelectionList* pSelectionList)
{
    CWHSV HSV;
    RGBColor.ToHSV(&HSV);

    CWSelection selection;

    // extract matching lines
    CWHorzLine* current_line = NULL;
    for(uint32_t y = Rect.TopY; y <= Rect.BottomY; y++)
    {
        current_line = NULL;
        for(uint32_t x = Rect.TopX; x <= Rect.BottomX; x++)
        {
            if(IsPixelSimilar(x, y, HSV, iTolerHue, iTolerSaturation, iTolerValue))
            {
                if(current_line == NULL)
                {
                    current_line = new CWHorzLine(x, x, y);
                    selection.Add(current_line);
                }
                else
                    current_line->EndX++;
            }
            else
                current_line = NULL;
        }
    }

    pSelectionList->Clear();
    selection.SplitIntoObjects(pSelectionList);
}

void CWRawImage::AverageColor(const CWRect& rect, CWRGB* pRGB)
{
    uint32_t numpix = rect.Width() * rect.Height();
    if(numpix == 0)
    {
        pRGB->Red = 0;
        pRGB->Green = 0;
        pRGB->Blue = 0;
        return;
    }

    int32_t sum_r = 0;
    int32_t sum_g = 0;
    int32_t sum_b = 0;

    for(int y = rect.TopY; y <= rect.BottomY; y++)
    {
        for(int x = rect.TopX; x <= rect.BottomX; x++)
        {
            int buffpos = (Width * (y * 3)) + (x * 3);
            sum_r += Buffer[buffpos];
            sum_g += Buffer[buffpos + 1];
            sum_b += Buffer[buffpos + 2];
        }
    }

    pRGB->Red = sum_r / numpix;
    pRGB->Green = sum_g / numpix;
    pRGB->Blue = sum_b / numpix;
}

void CWRawImage::DrawHorzLine(int iStartX, int iEndX, int iY, const CWRGB& rgb)
{
    int buffpos = (Width * (iY * 3)) + (iStartX * 3);

    int length = iEndX - iStartX + 1;
    for(int i = 0; i < length; i++)
    {
        Buffer[buffpos] = rgb.Red; buffpos++;
        Buffer[buffpos] = rgb.Green; buffpos++;
        Buffer[buffpos] = rgb.Blue; buffpos++;
    }
}

void CWRawImage::DrawHorzLine(const CWHorzLine& line, const CWRGB& rgb)
{
    DrawHorzLine(line.StartX, line.EndX, line.Y, rgb);
}

void CWRawImage::DrawHorzLine(CWHorzLine* pLine, const CWRGB& rgb)
{
    DrawHorzLine(pLine->StartX, pLine->EndX, pLine->Y, rgb);
}

void CWRawImage::FillRect(const CWRect& rect, const CWRGB& rgb)
{
    for(int y = rect.TopY; y <= rect.BottomY; y++)
        DrawHorzLine(rect.TopX, rect.BottomX, y, rgb);
}

void CWRawImage::FillSelection(const CWSelection& selection, const CWRGB& rgb)
{
    int count = selection.Count();
    for(int i = 0; i < count; i++)
    {
        CWHorzLine* line = selection.Items[i];
        DrawHorzLine(line, rgb);
    }
}

void CWRawImage::DrawPixmap(const string& sPixmap, uint32_t iX, uint32_t iY, const CWRGB& rForeground, const CWRGB& rBackground, bool bTransparentFG, bool bTransparentBG, int* pWidth, int* pHeight)
{
    if(bTransparentFG && bTransparentBG)
        return;

    int width = 0;
    int height = 0;

    int x = iX;
    int y = iY;
    int counter = 0;
    while(sPixmap[counter] != '\0')
    {
        while(sPixmap[counter] == '\r')
        {
            x = iX;
            y++;
            counter++;
            if(sPixmap[counter] == '\n')
                counter++;
        }

        while(sPixmap[counter] == '\n')
        {
            x = iX;
            y++;
            counter++;
            if(sPixmap[counter] == '\r')
                counter++;
        }

        if(sPixmap[counter] != '\0')
        {
            if(x - iX > width) width = (x - iX) + 1;
            if(y - iY > height) height = (y - iY) + 1;

            if(sPixmap[counter] == '0' && !bTransparentBG)
                SetPixelRGB(x, y, rBackground);
            else
            {
                if(sPixmap[counter] == '1' && !bTransparentFG)
                    SetPixelRGB(x, y, rForeground);
            }
            x++;
            counter++;
        }
    }

    if(pWidth != NULL) *pWidth = width;
    if(pHeight != NULL) *pHeight = height;
}

void CWRawImage::Pixelize(const CWRect& Rect, uint32_t iPixelWidth, uint32_t iPixelHeight)
{
    CWRGB rgb;
    for(uint32_t y = Rect.TopY; y <= Rect.BottomY; y += iPixelHeight)
    {
        for(uint32_t x = Rect.TopX; x <= Rect.BottomX; x += iPixelWidth)
        {
            CWRect rect(x, y, x + iPixelWidth - 1, y + iPixelHeight - 1);
            if(rect.BottomX >= (int)Width) rect.BottomX = Width - 1;
            if(rect.BottomY >= (int)Height) rect.BottomY = Height - 1;

            AverageColor(rect, &rgb);

            // fill
            FillRect(rect, rgb);
        }
    }
}

void CWRawImage::Treshold(const CWRect& Rect, const CWRGB& RGBColor, uint8_t iTolerHue, uint8_t iTolerSaturation, uint8_t iTolerValue)
{
    CWHSV HSV;
    RGBColor.ToHSV(&HSV);

    CWRGB rgb_black(0, 0, 0);
    CWRGB rgb_white(255, 255, 255);
    for(uint32_t y = Rect.TopY; y <= Rect.BottomY; y++)
    {
        for(uint32_t x = Rect.TopX; x <= Rect.BottomX; x++)
        {
            if(IsPixelSimilar(x, y, HSV, iTolerHue, iTolerSaturation, iTolerValue))
                SetPixelRGB(x, y, rgb_white);
            else
                SetPixelRGB(x, y, rgb_black);
        }
    }
}

void CWRawImage::Desaturate(const CWRect& Rect)
{
    CWRGB rgb;
    CWHSV hsv;
    for(uint32_t y = Rect.TopY; y <= Rect.BottomY; y++)
    {
        for(uint32_t x = Rect.TopX; x <= Rect.BottomX; x++)
        {
            GetPixelRGB(x, y, &rgb);
            rgb.ToHSV(&hsv);
            rgb.Set(hsv.Value, hsv.Value, hsv.Value);
            SetPixelRGB(x, y, rgb);
        }
    }
}


