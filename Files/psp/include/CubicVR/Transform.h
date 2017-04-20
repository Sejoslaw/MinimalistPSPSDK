/*
    This file is part of CubicVR.

    CubicVR is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    CubicVR is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with CubicVR; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
    
    
    Source (c) 2003 by Charles J. Cliffe unless otherwise specified
    To contact me, e-mail or MSN to cj@cubicproductions.com or by ICQ#7188044
    http://www.cubicproductions.com
*/

#ifndef TRANSFORM_H
#define TRANSFORM_H

#define NUM_TEMPS 4


#include <CubicVR/cvr_defines.h>

#include <CubicVR/Matrix.h>
#include <CubicVR/XYZ.h>

#include <deque>


class IMPEXP Transform 
{
private:
	std::deque<Matrix*> matrixStack;				// transformation stack
	std::deque<Matrix*>::iterator matrixIterator;	// transformation stack iterator

	Matrix *transMatrix;		// current transformation matrix

	Matrix *tMatrix1_4[NUM_TEMPS];	// temporary matricies (1x4)
	Matrix *tMatrix4_4[NUM_TEMPS];	// temporary matricies (4x4)

	bool invalidated;
	void invalidate(void) { invalidated = true; }

public:
	Transform();
	~Transform();

	void pushMatrix();
	void popMatrix();

	void trans(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float ang, float x, float y, float z);
	void apply(XYZ &v_in, XYZ &v_out);
	void set(float *mat);
};


#endif

