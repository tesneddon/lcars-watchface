/*++
**  MODULE DESCRIPTION:
**
**      This is a Pebble Watchface App that displays the time in both
**  terrestrial earth time as well as the Star Trek stardate.
**
**  Thanks go to David Trimboli for developing his stardate calculation
**  algorithm, which is the basis for this watch face.  You can see all
**  the details at his webpage:
**
**      http://www.trimboli.name/stardate.html
**
**  AUTHOR:     Tim Sneddon
**
**  Copyright (c) 2013, Tim Sneddon <tim@sneddon.id.au>.
**
**  All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions
**  are met:
**
**      * Redistributions of source code must retain the above
**        copyright notice, this list of conditions and the following
**        disclaimer.
**      * Redistributions in binary form must reproduce the above
**        copyright notice, this list of conditions and the following
**        disclaimer in the documentation and/or other materials provided
**        with the distribution.
**      * Neither the name of the copyright owner nor the names of any
**        other contributors may be used to endorse or promote products
**        derived from this software without specific prior written
**        permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
**  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
**  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
**  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
**  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
**  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
**  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
**  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
**  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**  CREATION DATE: 15-OCT-2013
**
**  MODIFICATION HISTORY:
**
**      15-OCT-2013 V1.0    Sneddon     Initial coding.
**--
*/
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

/*
** Forward Declarations
*/

    void pbl_main(void *params);
    void handle_init(AppContextRef ctx);

/*
** Pebble App Identification
*/

#define MY_UUID { 0x4D, 0xF3, 0x89, 0x75, \
		  0xBE, 0xE6, 0x46, 0x03, \
		  0xAF, 0xC6, 0xA1, 0x7C, \
		  0x1F, 0x80, 0xFC, 0xCE }

PBL_APP_INFO(MY_UUID,
             "LCARS Watchface", "Tim Sneddon",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

/*
** Global storage.
*/

    HeapBitmap lcars;
    BitmapLayer lcars_layer;
    Window window;

void pbl_main(void *params) {
    PebbleAppHandlers handlers = {
    	.init_handler = &handle_init
    };
    app_event_loop(params, &handlers);
}


void handle_init(AppContextRef ctx) {

    window_init(&window, "LCARS Watchface");
    window_stack_push(&window, true /* Animated */);
    window_set_background_color(&window, GColorBlack);

    resource_init_current_app(&APP_RESOURCES);

    heap_bitmap_init(&lcars, RESOURCE_ID_LCARS);
    bitmap_layer_init(&lcars_layer, GRect(0, 0, 144, 168));
    bitmap_layer_set_bitmap(&lcars_layer, &lcars.bmp);
    layer_add_child(&window.layer, &lcars_layer.layer);
}


