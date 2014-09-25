//
//  canonball.h
//
//  Created by Jon Christopher on 9/23/14.
//  Copyright (c) 2014 hoot. All rights reserved.
//

#pragma once
#define __MACOS__
#include <string>
#include "EDSDK.h"

extern "C" {
    int take_picture(int camera_index);
}

extern "C" {
  int download_files(int camera_index, const char* folder);
}

