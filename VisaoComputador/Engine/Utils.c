//
//  Utils.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifdef OSX
#include <stdio.h>
#else
// TODO: Márcio
#endif

float Max3(float a, float b, float c) {
    
    if (a > b && a > c)
        return a;
    else if (b > c)
        return b;
    else
        return c;
}

float Min3(float x, float y, float z)
{
    if (x < y)
        if (x < z)
            return x;
    
    if (y < z)
        return y;
    
    return z;
}
