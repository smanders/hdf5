/****************************************************************************
 * NCSA HDF                                                                 *
 * Software Development Group                                               *
 * National Center for Supercomputing Applications                          *
 * University of Illinois at Urbana-Champaign                               *
 * 605 E. Springfield, Champaign IL 61820                                   *
 *                                                                          *
 * For conditions of distribution and use, see the accompanying             *
 * hdf/COPYING file.                                                        *
 *                                                                          *
 ****************************************************************************/

#ifdef RCSID
static char RcsId[] = "$Revision$";
#endif

/* $Id$ */

/***********************************************************
*
* Test program:  tfile
*
* Test the low-level file I/O features.
*
*************************************************************/

#include <testhdf5.h>

#include <H5private.h>
#include <H5Bprivate.h>
#include <H5Cprivate.h>
#include <H5Mprivate.h>

#define F1_USERBLOCK_SIZE  0
#define F1_OFFSET_SIZE     4
#define F1_LENGTH_SIZE     4
#define F1_SYM_LEAF_K	   4
#define F1_SYM_INTERN_K	   16
#define FILE1   "tfile1.h5"

#define F2_USERBLOCK_SIZE  512
#define F2_OFFSET_SIZE     8
#define F2_LENGTH_SIZE     8
#define F2_SYM_LEAF_K	   8
#define F2_SYM_INTERN_K	   32
#define FILE2   "tfile2.h5"

#define F3_USERBLOCK_SIZE  0
#define F3_OFFSET_SIZE     F2_OFFSET_SIZE
#define F3_LENGTH_SIZE     F2_LENGTH_SIZE
#define F3_SYM_LEAF_K	   F2_SYM_LEAF_K
#define F3_SYM_INTERN_K	   F2_SYM_INTERN_K
#define FILE3   "tfile3.h5"

/****************************************************************
**
**  test_file_create(): Low-level file creation I/O test routine.
** 
****************************************************************/
static void test_file_create(void)
{
    hid_t fid1,fid2,fid3;    /* HDF5 File IDs */
    hid_t tmpl1,tmpl2;       /* File creation templates */
    size_t parm;           /* File-creation parameters */
    size_t parm2;          /* File-creation parameters */
    int iparm;
    herr_t ret;         /* Generic return value */

    /* Output message about test being performed */
    MESSAGE(5, ("Testing Low-Level File Creation I/O\n"));

    /* Create first file */
    fid1=H5Fcreate(FILE1,H5ACC_OVERWRITE,0,0);
    CHECK(fid1,FAIL,"H5Fcreate");

    /* Try to create first file again (should fail) */
    fid2=H5Fcreate(FILE1,H5ACC_OVERWRITE,0,0);
    VERIFY(fid2,FAIL,"H5Fcreate");

    /* Get the file-creation template */
    tmpl1 = H5Fget_create_template (fid1);
    CHECK(tmpl1,FAIL,"H5Fget_create_template");

    /* Get the file-creation parameters */
    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_USERBLOCK, &parm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm,F1_USERBLOCK_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_ADDR, &parm2);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm2,F1_OFFSET_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_SIZE, &parm2);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm2,F1_LENGTH_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SYM_LEAF_K, &iparm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(iparm,F1_SYM_LEAF_K,"H5Cget_prop");

    ret =H5Cget_prop (tmpl1, H5F_SYM_INTERN_K, &iparm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(iparm,F1_SYM_INTERN_K,"H5Cget_prop");

    /* Release file-creation template */
    ret=H5Mclose(tmpl1);
    CHECK(ret,FAIL,"H5Mrelease");
    
    /* Double-check that the atom has been vaporized */
    ret=H5Mclose(tmpl1);
    VERIFY(ret,FAIL,"H5Mrelease");

    /* Create a new file with a non-standard file-creation template */
    tmpl1 = H5Ccreate (H5C_FILE_CREATE);
    CHECK(tmpl1,FAIL,"H5Cnew");

    /* Set the new file-creation parameters */
    parm=F2_USERBLOCK_SIZE;
    ret = H5Cset_prop (tmpl1, H5F_SIZEOF_USERBLOCK, parm);
    CHECK(ret,FAIL,"H5Cset_prop");

    parm2=F2_OFFSET_SIZE;
    ret = H5Cset_prop (tmpl1, H5F_SIZEOF_ADDR, parm2);
    CHECK(ret,FAIL,"H5Cset_prop");

    parm2=F2_LENGTH_SIZE;
    ret = H5Cset_prop (tmpl1, H5F_SIZEOF_SIZE, parm2);
    CHECK(ret,FAIL,"H5Cset_prop");

    ret = H5Cset_prop (tmpl1, H5F_SYM_LEAF_K, F2_SYM_LEAF_K);
    CHECK(ret,FAIL,"H5Cset_prop");

    ret = H5Cset_prop (tmpl1, H5F_SYM_INTERN_K, F2_SYM_INTERN_K);
    CHECK(ret,FAIL,"H5Cset_prop");

    /* Try to create second file, with non-standard file-creation template params */
    fid2=H5Fcreate(FILE2,H5ACC_OVERWRITE,tmpl1,0);
    CHECK(fid2,FAIL,"H5Fcreate");

    /* Release file-creation template */
    ret=H5Mclose(tmpl1);
    CHECK(ret,FAIL,"H5Mrelease");
    
    /* Get the file-creation template */
    tmpl1=H5Fget_create_template(fid2);
    CHECK(tmpl1,FAIL,"H5Fget_create_template");

    /* Get the file-creation parameters */
    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_USERBLOCK, &parm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm,F2_USERBLOCK_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_SIZE, &parm2);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm2,F2_LENGTH_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_ADDR, &parm2);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm2,F2_OFFSET_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SYM_LEAF_K, &iparm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(iparm,F2_SYM_LEAF_K,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SYM_INTERN_K, &iparm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(iparm,F2_SYM_INTERN_K,"H5Cget_prop");

    /* Clone the file-creation template */
    tmpl2=H5Mcopy(tmpl1);
    CHECK(tmpl2,FAIL,"H5Mcopy");

    /* Release file-creation template */
    ret=H5Mclose(tmpl1);
    CHECK(ret,FAIL,"H5Mrelease");

    /* Set the new file-creation parameter */
    parm=F3_USERBLOCK_SIZE;
    ret = H5Cset_prop (tmpl2, H5F_SIZEOF_USERBLOCK, parm);
    CHECK(ret,FAIL,"H5Cset_prop");

    /* Try to create second file, with non-standard file-creation template params */
    fid3=H5Fcreate(FILE3,H5ACC_OVERWRITE,tmpl2,0);
    CHECK(fid3,FAIL,"H5Fcreate");

    /* Release file-creation template */
    ret=H5Mclose(tmpl2);
    CHECK(ret,FAIL,"H5Mrelease");

    /* Get the file-creation template */
    tmpl1=H5Fget_create_template(fid3);
    CHECK(tmpl1,FAIL,"H5Fget_create_template");

    /* Get the file-creation parameters */
    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_USERBLOCK, &parm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm,F3_USERBLOCK_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_ADDR, &parm2);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm2,F3_LENGTH_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_SIZE, &parm2);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm2,F3_OFFSET_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SYM_LEAF_K, &iparm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(iparm,F3_SYM_LEAF_K,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SYM_INTERN_K, &iparm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(iparm,F3_SYM_INTERN_K,"H5Cget_prop");

    /* Release file-creation template */
    ret=H5Mclose(tmpl1);
    CHECK(ret,FAIL,"H5Mrelease");

    /* Close first file */
    ret=H5Fclose(fid1);
    CHECK(ret,FAIL,"H5Fclose");

    /* Close second file */
    ret=H5Fclose(fid2);
    CHECK(ret,FAIL,"H5Fclose");

    /* Close third file */
    ret=H5Fclose(fid3);
    CHECK(ret,FAIL,"H5Fclose");
}   /* test_file_create() */


/****************************************************************
**
**  test_file_open(): Low-level file open I/O test routine.
** 
****************************************************************/
static void test_file_open(void)
{
    hid_t fid1;    /* HDF5 File IDs */
    hid_t tmpl1;       /* File creation templates */
    size_t parm;           /* File-creation parameters */
    size_t parm2;          /* File-creation parameters */
    int iparm;
    herr_t ret;         /* Generic return value */

    /* Output message about test being performed */
    MESSAGE(5, ("Testing Low-Level File Opening I/O\n"));

    /* Open first file */
    fid1=H5Fopen(FILE2,H5ACC_WRITE,0);
    CHECK(fid1,FAIL,"H5Fopen");

    /* Get the file-creation template */
    tmpl1=H5Fget_create_template(fid1);
    CHECK(tmpl1,FAIL,"H5Fget_create_template");

    /* Get the file-creation parameters */
    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_USERBLOCK, &parm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm,F2_USERBLOCK_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_ADDR, &parm2);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm2,F2_OFFSET_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SIZEOF_SIZE, &parm2);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(parm2,F2_LENGTH_SIZE,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SYM_LEAF_K, &iparm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(iparm,F2_SYM_LEAF_K,"H5Cget_prop");

    ret = H5Cget_prop (tmpl1, H5F_SYM_INTERN_K, &iparm);
    CHECK(ret,FAIL,"H5Cget_prop");
    VERIFY(iparm,F2_SYM_INTERN_K,"H5Cget_prop");

    /* Release file-creation template */
    ret=H5Mclose(tmpl1);
    CHECK(ret,FAIL,"H5Mrelease");
    
    /* Close first file */
    ret=H5Fclose(fid1);
    CHECK(ret,FAIL,"H5Fclose");
}   /* test_file_open() */


/****************************************************************
**
**  test_file(): Main low-level file I/O test routine.
** 
****************************************************************/
void test_file(void)
{
    /* Output message about test being performed */
    MESSAGE(5, ("Testing Low-Level File I/O\n"));

    test_file_create();     /* Test file creation (also creation templates) */
    test_file_open();       /* Test file opening */
}   /* test_file() */

