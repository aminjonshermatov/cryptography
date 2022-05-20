//
// Created by aminjonshermatov on 5/20/2022.
//
#include "stdio.h"
#include "lib/BigDigits/bigd.h"
#include "lib/BigDigits/bigdigits.h"

int main(int argc, char **argv) {
    BIGD p, q;
    bdNewVars(&p, &q, NULL);
    bdConvFromHex(p, "8000000000000000000000000000000000000000000000000000000000000431");
    bdConvFromHex(p, "8000000000000000000000000000000150FE8A1892976154C59CFC193ACCF5B3");

    bdPrintHex("0x", p, "\n");
    bdPrintHex("0x", q, "\n");

    bdFreeVars(&p, &q, NULL);
    return 0;
}