#ifndef _ALI_HENRY_DRV_DBGFS_H
#define _ALI_HENRY_DRV_DBGFS_H

#include "ali_henry_priv.h"

#ifdef CONFIG_DEBUG_FS
void henry_dbgfs_create(struct henry_drv *drv);
void henry_dbgfs_remove(struct henry_drv *drv);
int henry_dbgfs_add_session(struct henry_session *sess);
int henry_dbgfs_del_session(struct henry_session *sess);
#else
inline void henry_dbgfs_create(struct henry_drv *drv) {};
inline void henry_dbgfs_remove(struct henry_drv *drv) {};
inline int henry_dbgfs_add_session(struct henry_session *sess)
{
	return -ENOSYS;
}
inline int henry_dbgfs_del_session(struct henry_session *sess)
{
	return -ENOSYS;
}
#endif

#endif
