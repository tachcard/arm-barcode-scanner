// Bridge between main.c and C++ world
/*
 * Fixes by:
 * Company: Tachcard Limited
 * Website: http://www.tachcard.com/
 * Email: rio@tachcard.com
 * Authors: Ilya Ratovsky, Bogdanov Maksim
 * Date: 04-05-2014
 */
#include <stdint.h>
#include <stdbool.h>
#include <sstream>

#include <ImageReaderSource.h>

#include <zxing/common/FastHybridBinarizer.h>
#include <zxing/common/HybridBinarizer.h>

#include <zxing/common/Counted.h>
#include <zxing/Binarizer.h>

//#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/MultiFormatReader.h>
//#include <zxing/oned/EAN8Reader.h>

//#include <zxing/oned/UPCAReader.h>

#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>
#include "stm32f4_discovery_lcd.h"

extern "C" void Delay(uint32_t nTime);

using namespace std;
using namespace zxing;

FastHybridBinarizer *binarizer;
Ref<BitMatrix> binary;
bool more = true;
int width_;
int height_;

extern "C" void cppInit(int width, int height) {
    width_ = width;
    height_ = height;
    binarizer = new FastHybridBinarizer(width, height);
    binary = new BitMatrix(width_, height_);
}

extern "C" void cppResetBinarizer(void) {
    binarizer->reset();
}

extern "C" void cppProcessBlockRow(uint8_t *blockRow) {
    binarizer->writeBlockRow(blockRow);
}

extern "C" uint8_t *cppGetResults(void) {
    return binarizer->getResults();
}

vector<Ref<Result> > decode(Ref<BitMatrix> matrix, DecodeHints hints) {
//Ref<qrcode::QRCodeReader> reader(new qrcode::QRCodeReader);
//Ref<oned::EAN8Reader> reader(new oned::EAN8Reader);
//Ref<oned::UPCAReader> reader(new oned::UPCAReader);
    Ref<MultiFormatReader> reader(new MultiFormatReader);

    return vector < Ref<Result> > (1, reader->decode(matrix, hints));

//Ref<LuminanceSource> source(new ImageReaderSource(matrix, matrix->getWidth(), matrix->getHeight()));
//Ref<HybridBinarizer> binarizer2(new HybridBinarizer(source));

//Ref<BinaryBitmap> binary(new BinaryBitmap(binarizer2));
//return vector<Ref<Result> >(1, reader->decode(binary, hints));
}

extern "C" int read_image(char * scan_str) {
    vector<Ref<Result> > results;
    string cell_result;
    int res = -1;

    try {
        DecodeHints hints(DecodeHints::DEFAULT_HINT);
        hints.setTryHarder(false);
        binary->setBits((int *) binarizer->getResults());
        results = decode(binary, hints);
        res = 0;
    } catch (const ReaderException& e) {
        cell_result = "zxing::ReaderException: " + string(e.what());
        res = -2;
    } catch (const zxing::IllegalArgumentException& e) {
        cell_result = "zxing::IllegalArgumentException: " + string(e.what());
        res = -3;
    } catch (const zxing::Exception& e) {
        cell_result = "zxing::Exception: " + string(e.what());
        res = -4;
    } catch (const std::exception& e) {
        cell_result = "std::exception: " + string(e.what());
        res = -5;
    }

    for (size_t i = 0; i < results.size(); i++) {
        stringstream s;
        char buf[32];
        DCMI_CaptureCmd (DISABLE);
        if (more) {
            s << "Format: "
                    << BarcodeFormat::barcodeFormatNames[results[i]->getBarcodeFormat()]
                    << endl;
            s.get(buf, sizeof(buf));
            LCD_DisplayStringLine(LINE(2), (unsigned char*) buf);
            for (int j = 0; j < results[i]->getResultPoints()->size(); j++) {
                s.str("");
                s.clear();
                s << "Point[" << j << "]: "
                        << results[i]->getResultPoints()[j]->getX() << " "
                        << results[i]->getResultPoints()[j]->getY() << endl;
                s.get(buf, sizeof(buf));
                LCD_DisplayStringLine(LINE(3 + j), (unsigned char*) buf);
            }
        }

        s.str("");
        s.clear();
        s << results[i]->getText()->getText() << endl;
        s.get(buf, sizeof(buf));

        int str_index;
        str_index = 0;
        while (buf[str_index] != '\0' && str_index < 256) {
            scan_str[str_index] = buf[str_index];
            str_index++;
        }
        scan_str[str_index] = '\r';
        str_index++;
        scan_str[str_index] = '\n';
        str_index++;
        scan_str[str_index] = '\0';

        LCD_DisplayStringLine(LINE(7), (unsigned char*) buf);
        Delay(500);
        LCD_SetDisplayWindow(0, 0, 320, 240);
        LCD_WriteRAM_Prepare();
        DCMI_CaptureCmd (ENABLE);
    }

    return res;
}
