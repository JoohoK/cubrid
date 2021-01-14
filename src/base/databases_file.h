/*
 * Copyright 2008 Search Solution Corporation
 * Copyright 2016 CUBRID Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */


/*
 * databases_file.h - Configuration file parser
 *
 */

#ifndef _DATABASES_FILE_H_
#define _DATABASES_FILE_H_

#ident "$Id$"

#if !defined (DO_NOT_USE_CUBRIDENV)
/* Name of the environment variable pointing to database file */
#define DATABASES_ENVNAME "DATABASES"
#endif

#if defined(WINDOWS)
#define SECTION_START_CHAR '['
#define SECTION_END_CHAR   ']'
#endif /* WINDOWS */

/* name of the database file */
#define DATABASES_FILENAME "databases.txt"

/* max num of db-hosts */
#define MAX_NUM_DB_HOSTS        32

/*
 * DB_INFO
 *
 * Note: This is a descriptor structure for databases in the currently
 *    accessible directory file.
 */
typedef struct database_info DB_INFO;

struct database_info
{
  char *name;
  char *pathname;
  char **hosts;
  char *logpath;
  char *lobpath;
  DB_INFO *next;
  int num_hosts;
};

extern char *cfg_os_working_directory (void);

extern char *cfg_maycreate_get_directory_filename (char *buffer);
extern int cfg_read_directory (DB_INFO ** info_p, bool write_flag);
extern void cfg_write_directory (const DB_INFO * databases);

extern int cfg_read_directory_ex (int vdes, DB_INFO ** info_p, bool write_flag);
extern void cfg_write_directory_ex (int vdes, const DB_INFO * databases);

extern void cfg_free_directory (DB_INFO * databases);
#if defined(CUBRID_DEBUG)
extern void cfg_dump_directory (const DB_INFO * databases);
#endif
extern void cfg_update_db (DB_INFO * db_info_p, const char *path, const char *logpath, const char *lobpath,
			   const char *host);
extern DB_INFO *cfg_new_db (const char *name, const char *path, const char *logpath, const char *lobpath,
			    const char **hosts);
extern DB_INFO *cfg_find_db_list (DB_INFO * dir, const char *name);
extern DB_INFO *cfg_add_db (DB_INFO ** dir, const char *name, const char *path, const char *logpath,
			    const char *lobpath, const char *host);
extern DB_INFO *cfg_find_db (const char *db_name);
extern bool cfg_delete_db (DB_INFO ** dir_info_p, const char *name);

extern char **cfg_get_hosts (const char *prim_host, int *count, bool include_local_host);
extern void cfg_free_hosts (char **host_array);
extern char *cfg_create_host_list (const char *primary_host_name, bool append_local_host, int *cnt);

#endif /* _DATABASES_FILE_H_ */
