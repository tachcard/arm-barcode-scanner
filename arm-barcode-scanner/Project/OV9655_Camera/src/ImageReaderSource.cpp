/*
 *  Copyright 2010-2011 ZXing authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ImageReaderSource.h"
#include <zxing/LuminanceSource.h>
#include <zxing/InvertedLuminanceSource.h>
#include <zxing/common/IllegalArgumentException.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

using namespace zxing;

using std::string;
using std::ostringstream;
using zxing::Ref;
using zxing::ArrayRef;
using zxing::LuminanceSource;

ImageReaderSource::ImageReaderSource(Ref<BitMatrix> matrix_, int width,
		int height) :
		matrix(matrix_), Super(width, height) {
}

ArrayRef<char> ImageReaderSource::getRow(int y, ArrayRef<char> row) const {
	if (!row) {
		row = ArrayRef<char>(matrix->getWidth());
	}

	Ref<BitArray> rowMatrix = matrix->getRow(y,
			Ref<BitArray>(new BitArray(matrix->getWidth())));
	for (int i = 0; i < rowMatrix->getSize(); i++) {
		row[i] = (char) rowMatrix->get(i);
	}

	return row;
}

ArrayRef<char> ImageReaderSource::getMatrix() const {
	ArrayRef<char> result(matrix->getWidth() * matrix->getHeight());
	//ArrayRef<char> result(30000);
	char* m = &result[0];
	for (int y = 0; y < matrix->getHeight(); y++) {
		for (int x = 0; x < matrix->getWidth(); x++) {
			*m = (char) matrix->get(x, y);
			m++;
		}
	}

	return result;
}
