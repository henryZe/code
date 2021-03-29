#ifndef _ALI_HENRY_DRV_SYS_H
#define _ALI_HENRY_DRV_SYS_H

#include "ali_henry_priv.h"

int henry_sysfs_create(struct henry_drv *drv);
void henry_sysfs_remove(struct henry_drv *drv);

#endif
