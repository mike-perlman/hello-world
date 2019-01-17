#include <inttypes.h>

#ifndef SRC_PROTO_MPS7_H_
#define SRC_PROTO_MPS7_H_
#pragma pack(1)

#define MPS7_FORMAT		"MPS7"
#define ERR_BAD_RECORD	        -999
#define ERR_RECORD_MISCOUNT     -100
#define ERR_FILE_ERROR          -200
#define ERR_BAD_HEADER			-300

typedef enum __RECTYPE{Debit, Credit, StartAutoPay, EndAutoPay} RECTYPE;

typedef uint64_t USER_ID;

//////////////////////////////////////////////////
#define LEN_HEADER	      9

typedef struct __MPS7_HEADER {
	char format[4];
	char version;
	uint32_t record_count;
} MPS7_HEADER;


///////////////////////////////////////////////////
//define AUTOPAY_REC_LEN 13
//define DEBCRED_REC_LEN 21

typedef struct __MPS7_REC_DEBCRED {
	RECTYPE rec_type;
	uint32_t rawTimestamp;
	USER_ID userId;
	double amount;
} MPS7_REC_DEBCRED;


typedef struct __MPS7_REC_AUTOPAY {
	RECTYPE rec_type;
	uint32_t rawTimestamp;
	USER_ID userId;
} MPS7_REC_AUTOPAY;


typedef union __MPS7_RECORD {
	MPS7_REC_AUTOPAY autopay;
	MPS7_REC_DEBCRED debitCredit;
} MPS7_RECORD;


////////////////////////////////////////////////////
#define LEN_CENTS_SZ     30

typedef struct __MPS7_SUMMARY {
	int status;
	uint64_t debitTotalCents;
	uint64_t creditTotalCents;
	uint32_t qtyAutopayStart;
	uint32_t qtyAutopayEnds;
	char szCreditAmount[LEN_CENTS_SZ];
	char szDebitAmount[LEN_CENTS_SZ];
}MPS7_SUMMARY;

typedef struct __MPS7_USER_SUMMARY{
	USER_ID userId;
	MPS7_SUMMARY summary;
} MPS7_USER_SUMMARY;

/////////////////////////////////////////////////////
void init_rec(MPS7_RECORD *rec);
int read_header (FILE *fp, MPS7_HEADER *header);
int read_record(FILE *fp, MPS7_RECORD *rec);
void accumulate_summary(MPS7_SUMMARY *summary, MPS7_RECORD record);
MPS7_SUMMARY * mps7_file_summary(char *fname);
MPS7_USER_SUMMARY * mps7_user_summary(char *fname, uint64_t targetUser );
void print_summary(MPS7_SUMMARY *summary);
void print_user_credit_balance(MPS7_USER_SUMMARY *us);
void print_record(MPS7_RECORD *rec, int recNumber);
void formatMoney(MPS7_SUMMARY * s) ;
void set_endrun_status(MPS7_SUMMARY * out, int fileError, int returnCode,
						uint32_t expectedCount, uint32_t actualCount);
#endif /* SRC_PROTO_MPS7_H_ */
