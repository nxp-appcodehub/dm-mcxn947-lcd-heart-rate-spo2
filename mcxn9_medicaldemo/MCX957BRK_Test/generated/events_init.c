/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

void events_init(lv_ui *ui)
{
}

void video_play(lv_ui *ui)
{

}

static void screen_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_RELEASED:
	{
		lv_obj_t * act_scr = lv_scr_act();
		lv_disp_t * d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.screen_1_del == true)
				setup_scr_screen_1(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_1, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
		}
	}
		break;
	default:
		break;
	}
}

void events_init_screen(lv_ui *ui)
{
	//lv_obj_add_event_cb(ui->screen_btn_1, screen_btn_1_event_handler, LV_EVENT_ALL, ui);
}
