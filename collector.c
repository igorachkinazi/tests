#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

#define HFD_TRACE_CMD_FROM_TRANSPORT  1
#define HFD_TRACE_CMD_TO_LIBSDC       2
#define HFD_TRACE_CMD_FROM_LIBSDC     3
#define HFD_TRACE_CMD_REPLY_SENT      4
#define HFD_TRACE_CMD_FROM_INI        5
#define HFD_TRACE_CMD_TGT_DONE        6
#define HFD_TRACE_SKIPPED             7
#define HFD_TRACE_MAX_NUM             7

#define HFD_TRACE_READ_IO       0
#define HFD_TRACE_WRITE_IO      1
#define HFD_TRACE_WR_ZEROES_IO  2
#define HFD_TRACE_COMPARE_IO    3

typedef struct  __attribute__((packed)) s_hfd_trace_vol_lba
{
    uint16_t    unique_id;
    uint16_t    kvl_bits;
    timeval     timestamp;
    uint32_t    io_id_and_type;
    uint64_t    volId;
    uint64_t    lba;
    uint16_t    data_len;
    uint32_t    rc;
} t_hfd_trace_vol_lba;

const struct s_hfd_sample_description hfd_desc[HFD_SAMPLE_MAX_NUM] =
{
    {"allocateCommand","Command allocated"},
    {"onAsyncAllocCKCompletion","Async UD allocated"},
    {"nt_protocol_submit_command","Command from transport"},
    {"sdc_device_submit_io_cmd","Sumbitted to libSDC"},
    {"sdc_device_io_done","Completion from libSDC"},
    {"nt_protocol_fe_complete_cmd","Submitted reply to transport"},
    {"onCommandCompletionIntern", "Handle cmd from protocol"},
    {"sendCapsuleResp","Sent response to host"},
    {"onCompletion","Send to host complete"}
};

const char * const hfd_trace_desc[HFD_TRACE_MAX_NUM] =
{
        "nt_protocol_submit_command: Got command from transport",
        "sdc_device_submit_io_cmd: Sumbitted to libSDC",
        "nt_protocol_complete_be_cmd: Completion from libSDC",
        "OutboundQueue::onCompletion: reply sent to host",
        "ioh_NewRequest: from initiator",
        "ioh_NewRequest: done",
        " skipped trace entries",
};

int main(int    argc,
         char** argv)
{
    ;
}

