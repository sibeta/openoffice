/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// autogenerated file with codegen.pl

#include "preextstl.h"
#include "gtest/gtest.h"
#include "postextstl.h"

#include <basegfx/vector/b2isize.hxx>
#include <basegfx/range/b2irange.hxx>
#include <basegfx/point/b2ipoint.hxx>
#include <basegfx/polygon/b2dpolygon.hxx>
#include <basegfx/polygon/b2dpolygontools.hxx>
#include <basegfx/polygon/b2dpolypolygon.hxx>
#include <basegfx/polygon/b2dpolypolygontools.hxx>

#include <basebmp/color.hxx>
#include <basebmp/scanlineformats.hxx>
#include <basebmp/bitmapdevice.hxx>
#include <basebmp/debug.hxx>
#include "tools.hxx"

#include <iostream>
#include <fstream>

using namespace ::basebmp;

namespace
{
/*
        std::ofstream output("32bpp_test.dump");
        debugDump( rDevice, output );
        std::ofstream output2("32bpp_bmp.dump");
        debugDump( rBmp, output2 );
*/

class BmpTest : public ::testing::Test
{
protected:
    BitmapDeviceSharedPtr mpDevice1bpp;
    BitmapDeviceSharedPtr mpBmp1bpp;
    BitmapDeviceSharedPtr mpDevice32bpp;
    BitmapDeviceSharedPtr mpBmp32bpp;

    void implTestBmpBasics(const BitmapDeviceSharedPtr& rDevice,
                           const BitmapDeviceSharedPtr& rBmp)
    {
        rDevice->clear(Color(0));
        const Color aCol(0xFFFFFFFF);

        const basegfx::B2IRange aSourceRect(0,0,10,10);
        const basegfx::B2IRange aDestLeftTop(0,0,4,4);
        const basegfx::B2IRange aDestRightTop(6,0,10,4);
        const basegfx::B2IRange aDestLeftBottom(0,6,4,10);
        const basegfx::B2IRange aDestRightBottom(6,6,10,10);

        rDevice->drawBitmap(
            rBmp,
            aSourceRect,
            aDestLeftTop,
            DrawMode_PAINT );
        ASSERT_TRUE(countPixel( rDevice, aCol ) == 8) << "number of rendered pixel is not 8";

        rDevice->drawBitmap(
            rBmp,
            aSourceRect,
            aDestRightTop,
            DrawMode_PAINT );
        ASSERT_TRUE(countPixel( rDevice, aCol ) == 16) << "number of rendered pixel is not 16";

        rDevice->drawBitmap(
            rBmp,
            aSourceRect,
            aDestLeftBottom,
            DrawMode_PAINT );
        ASSERT_TRUE(countPixel( rDevice, aCol ) == 24) << "number of rendered pixel is not 24";

        rDevice->drawBitmap(
            rBmp,
            aSourceRect,
            aDestRightBottom,
            DrawMode_PAINT );
        ASSERT_TRUE(countPixel( rDevice, aCol ) == 32) << "number of rendered pixel is not 32";
    }

    void implTestBmpClip(const BitmapDeviceSharedPtr& rDevice,
                         const BitmapDeviceSharedPtr& rBmp)
    {
        rDevice->clear(Color(0));
        const Color aCol(0xFFFFFFFF);

        const basegfx::B2IRange aSourceRect(0,0,10,10);
        const basegfx::B2IRange aDestLeftTop(-2,-2,2,2);
        const basegfx::B2IRange aDestRightTop(8,-2,12,2);
        const basegfx::B2IRange aDestLeftBottom(-2,8,2,12);
        const basegfx::B2IRange aDestRightBottom(8,8,12,12);

        rDevice->drawBitmap(
            rBmp,
            aSourceRect,
            aDestLeftTop,
            DrawMode_PAINT );
        ASSERT_TRUE(countPixel( rDevice, aCol ) == 4) << "number of rendered pixel is not 4";

        rDevice->drawBitmap(
            rBmp,
            aSourceRect,
            aDestLeftBottom,
            DrawMode_PAINT );
        ASSERT_TRUE(countPixel( rDevice, aCol ) == 4) << "number of rendered pixel is not 4(c)";

        rDevice->drawBitmap(
            rBmp,
            aSourceRect,
            aDestRightBottom,
            DrawMode_PAINT );
        ASSERT_TRUE(countPixel( rDevice, aCol ) == 8) << "number of rendered pixel is not 8";
    }

public:
    virtual void SetUp()
    {
        const basegfx::B2ISize aSize(10,10);
        mpDevice1bpp = createBitmapDevice( aSize,
                                           true,
                                           Format::ONE_BIT_MSB_PAL );
        mpDevice32bpp = createBitmapDevice( aSize,
                                            true,
                                            Format::THIRTYTWO_BIT_TC_MASK );

        mpBmp1bpp = createBitmapDevice( aSize,
                                        true,
                                        Format::ONE_BIT_MSB_PAL );
        mpBmp32bpp = createBitmapDevice( aSize,
                                         true,
                                         Format::THIRTYTWO_BIT_TC_MASK );

        ::rtl::OUString aSvg = ::rtl::OUString::createFromAscii(
            "m 0 0h5v10h5v-5h-10z" );

        basegfx::B2DPolyPolygon aPoly;
        basegfx::tools::importFromSvgD( aPoly, aSvg, false, NULL );
        const Color aCol(0xFFFFFFFF);
        mpBmp1bpp->fillPolyPolygon(
            aPoly,
            aCol,
            DrawMode_PAINT );
        mpBmp32bpp->fillPolyPolygon(
            aPoly,
            aCol,
            DrawMode_PAINT );
    }
};

TEST_F(BmpTest, testBmpBasics)
{
    implTestBmpBasics( mpDevice1bpp, mpBmp1bpp );
    implTestBmpBasics( mpDevice32bpp, mpBmp32bpp );
}

TEST_F(BmpTest, testBmpClip)
{
    implTestBmpClip( mpDevice1bpp, mpBmp1bpp );
    implTestBmpClip( mpDevice32bpp, mpBmp32bpp );
}


}
