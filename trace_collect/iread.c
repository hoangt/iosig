/* This file is part of the Server-Push File Access Server (FAS) environment
 *
 *            <<<<  Add more info >>>
 ****************************************************************************
 *
 * Author:      Suren Byna (sbyna@iit.edu)
 *              Illinois Institute of Technology &
 *              Argonne National Laboratory
 * Created on:  03/09/2007
 * Modified on: 03/16/2007 by Suren Byna
 *
 * Funded by:   NSF, Award # CCF-0621435
 *
 * File name: pushio_init.c
 * Purpose  : Wrapper function for MPI_Init ()
 *            Initiates tracing.
 *
 * Modified on: 12/16/2009 by Huaiming Song
 */

#include "mpioimpl.h"
#include "mpiimpl.h"
#include "pushio_trace.h"

int MPI_File_iread(MPI_File mpi_fh, void *buf, int count,
		   MPI_Datatype datatype, MPI_Request * request)
{
    int ret_val;
    int dtsize;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    iorec->is_mpi_operation = 1;
    iorec->mpi_rank = thisrank;
    iorec->filedes = mpi_fh->fd_sys;
    iorec->file_pos = mpi_fh->fp_ind;
    MPI_Type_size(datatype, &dtsize);
    iorec->data_size = count * dtsize;
    iorec->op_time = tv;
    iorec->operation = MPI_IREAD;

    log_read_trace(iorec);
    PushIO_RTB_log(thisrank, iorec);

    ret_val = PMPI_File_iread(mpi_fh, buf, count, datatype, request);
    return ret_val;
}
