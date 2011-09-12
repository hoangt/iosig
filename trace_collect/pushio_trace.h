/* This file is part of the Server-Push File Access Server (FAS) environment
 *
 *            <<<<  Add more info >>>
 ****************************************************************************
 *
 * Author:      Suren Byna (sbyna@iit.edu)
 *              Illinois Institute of Technology &
 *              Argonne National Laboratory
 * Created on:  03/04/2007
 * Modified on: 03/16/2007 by Suren Byna
 *		03/26/2007 by Suren Byna, to add RTB
 *
 * Funded by:   NSF, Award # CCF-0621435
 *
 * File name: pushio_trace.h
 * Purpose  : 
 *
 */

#ifndef PUSHIO_TRACE_H
#define PUSHIO_TRACE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <assert.h>

#define MAX_NUM_PROCS 4
#define MAX_NUM_RTB_ENTRIES 1024

struct timeval init_tv;
FILE *out_fp;
FILE *fp_rank;

typedef struct PushIO_Trace_record_t {
    int is_mpi_operation;
    int mpi_rank;
    int filedes;
    long int file_pos;
    size_t data_size;
    struct timeval op_time;
    int operation;
} PushIO_Trace_record;

/* declare pointers to IO Request Trace Buffers.
   * One buffer for each process.
   * Implemented as doubly linked lists */

typedef struct PushIO_RTB_node_t {
    struct PushIO_RTB_node_t *prev_rtb_node;
    PushIO_Trace_record rtb_entry;
    struct PushIO_RTB_node_t *next_rtb_node;
} PushIO_RTB_node;

PushIO_RTB_node *iortb_head;
PushIO_RTB_node *iortb_tail;

/* end of add: shm 2009.12 */
PushIO_Trace_record *iorec;
int thisrank;
/* end of add: shm 2009.12 */

/* Maintain the number of entries in an RTB corresponding to a process  */
int num_entries;

/* PushIO RTB doubly linked list functions */

int PushIO_RTB_init(int rank);
void PushIO_RTB_log(int rank, PushIO_Trace_record * pushio_rec);
int PushIO_RTB_backup(int rank, PushIO_Trace_record pushio_rec);
int PushIO_RTB_remove(int rank, PushIO_RTB_node * rtb_node);
int PushIO_RTB_dump_trace(int rank);
int PushIO_RTB_file_traces(int rank);
int PushIO_RTB_finalize(int rank);

void init_log();
void end_log();
void log_read_trace(PushIO_Trace_record * pushio_rec);
int timeval_diff(struct timeval *result, struct timeval *x,
		 struct timeval *y);
void get_operation(char *operation, int rec_operation);

#define MPI_SEEK 	51
#define MPI_OPEN 	52
#define MPI_CLOSE 	53

#define MPI_READ 	101
#define MPI_IREAD 	102
#define MPI_READAT 	103
#define MPI_READALL 	104
#define MPI_READATALL 	105
#define MPI_IREADAT 	106
#define MPI_READSH 	107
#define MPI_IREADSH 	108
#define MPI_READORD 	109

#define MPI_WRITE 	151
#define MPI_IWRITE 	152
#define MPI_WRITEAT 	153
#define MPI_WRITEALL 	154
#define MPI_WRITEATALL 	155
#define MPI_IWRITEAT 	156
#define MPI_WRITESH 	157
#define MPI_IWRITESH 	158
#define MPI_WRITEORD 	159

#define READ 		201
#define WRITE 		202
#define SEEK 		203
#define OPEN 		204
#define CLOSE 		205

#endif
