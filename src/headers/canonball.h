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
    int inialize_sdk();
}

extern "C" {
    int terminate_sdk();
}

extern "C" {
    int open_camera_session(int camera_index);
}

extern "C" {
    int close_camera_session();
}

extern "C" {
    int take_picture();
}

extern "C" {
    int set_drive_mode();
}

extern "C" {
    int press_shutter_button();
}

extern "C" {
    int press_shutter_button_non_af();
}

extern "C" {
  int download_files(int sd_card_index, const char* folder);
}

