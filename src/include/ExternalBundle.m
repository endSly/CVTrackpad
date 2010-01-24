//
//  ExternalBundle.m
//  CVTrackpad
//
//  Created by Endika Gutiérrez Salas on 05/03/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "ExternalBundle.h"


@implementation ExternalBundle

+(char*) externalBundlePathFor:(const char*)filename 
{
    return strcpy(malloc(512), [[[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"Contents/gamedata"] cString]);
}

@end
