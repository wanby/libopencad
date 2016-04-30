/*******************************************************************************
 *  Project: libopencad
 *  Purpose: OpenSource CAD formats support library
 *  Author: Alexandr Borzykh, mush3d at gmail.com
 *  Author: Dmitry Baryshnikov, bishop.dev@gmail.com
 *  Language: C++
 *******************************************************************************
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2016 Alexandr Borzykh
 *  Copyright (c) 2016 NextGIS, <info@nextgis.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
*******************************************************************************/
#include "cadfilestreamio.h"

CADFileStreamIO::CADFileStreamIO(const char *pszFilePath) : CADFileIO(pszFilePath)
{

}

CADFileStreamIO::~CADFileStreamIO()
{

}

const char *CADFileStreamIO::ReadLine()
{
    // TODO: getline
    return NULL;
}

bool CADFileStreamIO::Eof()
{
    m_oFileStream.eof();
}

bool CADFileStreamIO::Open(int mode)
{
    std::ios_base::openmode io_mode = std::ios_base::in;
    if(mode & OpenMode::binary)
        io_mode |= std::ios_base::binary;

    if(mode & OpenMode::write)
        //io_mode |= std::ios_base::out;
        return false;

    m_oFileStream = std::ifstream ( m_pszFilePath, io_mode);

    if(m_oFileStream.is_open())
        m_bIsOpened = true;

    return m_bIsOpened;
}

bool CADFileStreamIO::Close()
{
    m_oFileStream.close();
    return CADFileIO::Close();
}

int CADFileStreamIO::Seek(long offset, CADFileIO::SeekOrigin origin)
{
    std::ios_base::seekdir direction;
    switch (origin) {
    case SeekOrigin::CUR:
        direction = std::ios_base::cur;
        break;
    case SeekOrigin::END:
        direction = std::ios_base::end;
        break;
    case SeekOrigin::BEG:
    default:
        direction = std::ios_base::beg;
        break;
    }

    return m_oFileStream.seekg(offset, direction).good() ? 0 : 1;
}

long CADFileStreamIO::Tell()
{
    return m_oFileStream.tellg();
}

size_t CADFileStreamIO::Read(void *ptr, size_t size)
{
    return m_oFileStream.read((char*)ptr, size).gcount();
}

size_t CADFileStreamIO::Write(void *ptr, size_t size)
{
    // unsupported
    return 0;
}

void CADFileStreamIO::Rewind()
{
    m_oFileStream.seekg(0, std::ios_base::beg);
}
