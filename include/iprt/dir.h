 * Copyright (C) 2006-2020 Oracle Corporation
/** Ignore umask when applying the mode. */
#define RTDIRCREATE_FLAGS_IGNORE_UMASK                      RT_BIT(3)
#define RTDIRCREATE_FLAGS_VALID_MASK                        UINT32_C(0x0000000f)
 * Creates a directory including all non-existing parent directories.
/**
 * Creates a directory including all non-existing parent directories.
 *
 * @returns iprt status code.
 * @param   pszPath     Path to the directory to create.
 * @param   fMode       The mode of the new directories.
 * @param   fFlags      Create flags, RTDIRCREATE_FLAGS_*.
 */
RTDECL(int) RTDirCreateFullPathEx(const char *pszPath, RTFMODE fMode, uint32_t fFlags);

/**
 * Changes the mode flags of an open directory.
 *
 * The API requires at least one of the mode flag sets (Unix/Dos) to
 * be set. The type is ignored.
 *
 * @returns iprt status code.
 * @param   hDir                Handle to the open directory.
 * @param   fMode               The new file mode, see @ref grp_rt_fs for details.
 */
RTDECL(int) RTDirSetMode(RTDIR hDir, RTFMODE fMode);

