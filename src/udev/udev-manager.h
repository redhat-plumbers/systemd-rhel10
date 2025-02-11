/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include <stdbool.h>

#include "sd-device.h"
#include "sd-event.h"

#include "hashmap.h"
#include "macro.h"
#include "time-util.h"
#include "udev-ctrl.h"
#include "udev-def.h"

typedef struct Event Event;
typedef struct UdevRules UdevRules;
typedef struct Worker Worker;

typedef struct Manager {
        sd_event *event;
        Hashmap *workers;
        LIST_HEAD(Event, events);
        char *cgroup;
        int log_level;

        UdevRules *rules;
        Hashmap *properties;

        sd_device_monitor *monitor;
        UdevCtrl *ctrl;
        int worker_watch[2];

        /* used by udev-watch */
        int inotify_fd;
        sd_event_source *inotify_event;

        sd_event_source *kill_workers_event;

        usec_t last_usec;

        ResolveNameTiming resolve_name_timing;
        unsigned children_max;
        usec_t exec_delay_usec;
        usec_t timeout_usec;
        int timeout_signal;
        bool blockdev_read_only;

        bool stop_exec_queue;
        bool exit;
} Manager;

Manager* manager_new(void);
Manager* manager_free(Manager *manager);
DEFINE_TRIVIAL_CLEANUP_FUNC(Manager*, manager_free);

void manager_adjust_arguments(Manager *manager);
int manager_init(Manager *manager);
int manager_main(Manager *manager);

bool devpath_conflict(const char *a, const char *b);
