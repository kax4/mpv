/*
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPLAYER_VD_H
#define MPLAYER_VD_H

#include "video/mp_image.h"
#include "core/mpc_info.h"
#include "demux/stheader.h"

typedef struct mp_codec_info vd_info_t;

struct demux_packet;

/* interface of video decoder drivers */
typedef struct vd_functions
{
    const vd_info_t *info;
    int (*init)(sh_video_t *sh);
    void (*uninit)(sh_video_t *sh);
    int (*control)(sh_video_t *sh, int cmd, void *arg);
    struct mp_image *(*decode)(struct sh_video *sh, struct demux_packet *pkt,
                               void *data, int len, int flags,
                               double *reordered_pts);
} vd_functions_t;

// NULL terminated array of all drivers
extern const vd_functions_t *const mpcodecs_vd_drivers[];

#define VDCTRL_RESYNC_STREAM 8 // reset decode state after seeking
#define VDCTRL_QUERY_UNSEEN_FRAMES 9 // current decoder lag
#define VDCTRL_RESET_ASPECT 10 // reinit filter/VO chain for new aspect ratio

int mpcodecs_config_vo(sh_video_t *sh, int w, int h, unsigned int outfmt);

#endif /* MPLAYER_VD_H */
