/* SPDX-License-Identifier: LGPL-2.1-or-later */

#include "varlink-io.systemd.UserDatabase.h"

static SD_VARLINK_DEFINE_METHOD_FULL(
                GetUserRecord,
                SD_VARLINK_SUPPORTS_MORE,
                SD_VARLINK_DEFINE_INPUT(uid, SD_VARLINK_INT, SD_VARLINK_NULLABLE),
                SD_VARLINK_DEFINE_INPUT(userName, SD_VARLINK_STRING, SD_VARLINK_NULLABLE),
                SD_VARLINK_FIELD_COMMENT("Names to search for in a fuzzy fashion."),
                SD_VARLINK_DEFINE_INPUT(fuzzyNames, SD_VARLINK_STRING, SD_VARLINK_NULLABLE|SD_VARLINK_ARRAY),
                SD_VARLINK_FIELD_COMMENT("User dispositions to limit search by."),
                SD_VARLINK_DEFINE_INPUT(dispositionMask, SD_VARLINK_STRING, SD_VARLINK_NULLABLE|SD_VARLINK_ARRAY),
                SD_VARLINK_FIELD_COMMENT("Minimum UID to restrict search too."),
                SD_VARLINK_DEFINE_INPUT(uidMin, SD_VARLINK_INT, SD_VARLINK_NULLABLE),
                SD_VARLINK_FIELD_COMMENT("Maximum UID to restrict search too."),
                SD_VARLINK_DEFINE_INPUT(uidMax, SD_VARLINK_INT, SD_VARLINK_NULLABLE),
                SD_VARLINK_DEFINE_INPUT(service, SD_VARLINK_STRING, 0),
                SD_VARLINK_DEFINE_OUTPUT(record, SD_VARLINK_OBJECT, 0),
                SD_VARLINK_DEFINE_OUTPUT(incomplete, SD_VARLINK_BOOL, SD_VARLINK_NULLABLE));

static SD_VARLINK_DEFINE_METHOD_FULL(
                GetGroupRecord,
                SD_VARLINK_SUPPORTS_MORE,
                SD_VARLINK_DEFINE_INPUT(gid, SD_VARLINK_INT, SD_VARLINK_NULLABLE),
                SD_VARLINK_DEFINE_INPUT(groupName, SD_VARLINK_STRING, SD_VARLINK_NULLABLE),
                SD_VARLINK_FIELD_COMMENT("Additional names to search for in a fuzzy fashion."),
                SD_VARLINK_DEFINE_INPUT(fuzzyNames, SD_VARLINK_STRING, SD_VARLINK_NULLABLE|SD_VARLINK_ARRAY),
                SD_VARLINK_FIELD_COMMENT("Group dispositions to limit search by."),
                SD_VARLINK_DEFINE_INPUT(dispositionMask, SD_VARLINK_STRING, SD_VARLINK_NULLABLE|SD_VARLINK_ARRAY),
                SD_VARLINK_FIELD_COMMENT("Minimum GID to restrict search too."),
                SD_VARLINK_DEFINE_INPUT(gidMin, SD_VARLINK_INT, SD_VARLINK_NULLABLE),
                SD_VARLINK_FIELD_COMMENT("Maximum GID to restrict search too."),
                SD_VARLINK_DEFINE_INPUT(gidMax, SD_VARLINK_INT, SD_VARLINK_NULLABLE),
                SD_VARLINK_DEFINE_INPUT(service, SD_VARLINK_STRING, 0),
                SD_VARLINK_DEFINE_OUTPUT(record, SD_VARLINK_OBJECT, 0),
                SD_VARLINK_DEFINE_OUTPUT(incomplete, SD_VARLINK_BOOL, SD_VARLINK_NULLABLE));

static SD_VARLINK_DEFINE_METHOD_FULL(
                GetMemberships,
                SD_VARLINK_SUPPORTS_MORE,
                SD_VARLINK_DEFINE_INPUT(userName, SD_VARLINK_STRING, SD_VARLINK_NULLABLE),
                SD_VARLINK_DEFINE_INPUT(groupName, SD_VARLINK_STRING, SD_VARLINK_NULLABLE),
                SD_VARLINK_DEFINE_INPUT(service, SD_VARLINK_STRING, 0),
                SD_VARLINK_DEFINE_OUTPUT(userName, SD_VARLINK_STRING, 0),
                SD_VARLINK_DEFINE_OUTPUT(groupName, SD_VARLINK_STRING, 0));

static SD_VARLINK_DEFINE_ERROR(NoRecordFound);
static SD_VARLINK_DEFINE_ERROR(BadService);
static SD_VARLINK_DEFINE_ERROR(ServiceNotAvailable);
static SD_VARLINK_DEFINE_ERROR(ConflictingRecordFound);
static SD_VARLINK_DEFINE_ERROR(EnumerationNotSupported);
static SD_VARLINK_DEFINE_ERROR(NonMatchingRecordFound);

/* As per https://systemd.io/USER_GROUP_API/ */
SD_VARLINK_DEFINE_INTERFACE(
                io_systemd_UserDatabase,
                "io.systemd.UserDatabase",
                &vl_method_GetUserRecord,
                &vl_method_GetGroupRecord,
                &vl_method_GetMemberships,
                &vl_error_NoRecordFound,
                &vl_error_BadService,
                &vl_error_ServiceNotAvailable,
                &vl_error_ConflictingRecordFound,
                SD_VARLINK_SYMBOL_COMMENT("Error indicating that there's a user record matching the primary UID/GID or user/group, but that doesn't match the additional specified matches."),
                &vl_error_NonMatchingRecordFound,
                &vl_error_EnumerationNotSupported);
