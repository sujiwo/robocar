#include "zmp/IpmManager.h"
#include <string.h>
#include <stdio.h>
#include "NetpbmWriter.h"


int main (int argc, char *argv[])
{
        zmp::zrc::IpmManager ipmm;

        ipmm.Init ();
        ipmm.StopImap ();
        if (!ipmm.Reset ())
                printf ("Reset failed\n");

// modify program type to `none@
        if(!ipmm.LoadProgram(zmp::zrc::IMAP_ALG_STEREO_OBSTACLES_1))
                printf ("LoadProgram failed\n");

        if (!ipmm.StartImap ())
                printf ("Start failed\n");

// select image from source, uncorrected against distortion
        if(!ipmm.SelectImageOutput(zmp::zrc::SOF_INPUT_R))
                printf ("SelectImageOutput failed\n");

	if (!ipmm.SelectResultOutput(zmp::zrc::SOR_RESULT_LANE))
		printf ("SelectResultOutput failed\n");
       
	while (true) { 
		int ctr=0;
		ipmm.Wait ();

		if (ipmm.CollectResult()) {
			printf ("Result collected\n");
		}
		else {
			printf ("No result collected\n");
		}

		if (ipmm.CollectImage()) {
			printf ("Success collecting, size: %d\n", ipmm.ImageLength());
			char *imgdata = new char[ipmm.ImageLength()];
			memcpy (imgdata, ipmm.ImageData(), ipmm.ImageLength());
			NetpbmWriter::write ("testrbc.pgm", 640, 240, (uint8_t*)imgdata);
			break;
		}
		else {
			printf ("No image collected, Size: %d\n", ipmm.ImageLength());
		}
	}
}
