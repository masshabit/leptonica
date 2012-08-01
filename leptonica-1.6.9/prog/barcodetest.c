/*====================================================================*
 -  Copyright (C) 2001 Leptonica.  All rights reserved.
 -
 -  Redistribution and use in source and binary forms, with or without
 -  modification, are permitted provided that the following conditions
 -  are met:
 -  1. Redistributions of source code must retain the above copyright
 -     notice, this list of conditions and the following disclaimer.
 -  2. Redistributions in binary form must reproduce the above
 -     copyright notice, this list of conditions and the following
 -     disclaimer in the documentation and/or other materials
 -     provided with the distribution.
 -
 -  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 -  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 -  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 -  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL ANY
 -  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 -  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 -  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 -  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 -  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 -  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 -  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *====================================================================*/

/*
 * barcodetest.c
 *
 *      barcodetest filein
 *
 *  For each barcode in the image, if the barcode format is supported,
 *  this deskews and crops it, and then decodes it twice:
 *      (1) as is (deskewed)
 *      (2) after 180 degree rotation
 */

#include "allheaders.h"
#include "readbarcode.h"

main(int    argc,
     char **argv)
{
char        *filein;
PIX         *pixs;
SARRAY      *saw1, *saw2, *saw3, *sad1, *sad2, *sad3;
static char  mainName[] = "barcodetest";

    if (argc != 2)
	exit(ERROR_INT(" Syntax:  barcodetest filein", mainName, 1));

    filein = argv[1];
    if ((pixs = pixRead(filein)) == NULL)
	exit(ERROR_INT("pixs not made", mainName, 1));

    sad1 = pixProcessBarcodes(pixs, L_BF_ANY, L_USE_WIDTHS, &saw1, 0);
    sarrayWrite("/tmp/junksaw1", saw1);
    sarrayWrite("/tmp/junksad1", sad1);
    sarrayDestroy(&saw1);
    sarrayDestroy(&sad1);

    pixRotate180(pixs, pixs);
    sad2 = pixProcessBarcodes(pixs, L_BF_ANY, L_USE_WIDTHS, &saw2, 0);
    sarrayWrite("/tmp/junksaw2", saw2);
    sarrayWrite("/tmp/junksad2", sad2);
    sarrayDestroy(&saw2);
    sarrayDestroy(&sad2);

/*    sad3 = pixProcessBarcodes(pixs, L_BF_ANY, L_USE_WINDOW, &saw3, 1);
    sarrayWrite("/tmp/junksaw3", saw3);
    sarrayWrite("/tmp/junksad3", sad3);
    sarrayDestroy(&saw3);
    sarrayDestroy(&sad3); */

    pixDestroy(&pixs);
    exit(0);
}

