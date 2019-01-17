#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include "mps7.h"
#include "bitsbytes.h"

#define CLEAN_READ(x)  (!ferror(x) && !feof(x))
#define TO_PENNIES(dbl) (dbl > 0 ? floor(dbl * 100.0 - 0.5) : ceil(dbl * 100 - 0.5));
#define NET_BALANCE_INT(cr,dr)	(cr < 0 ? dr+cr : dr-cr)

int convertFloatsTo754;
char * recTypes[] = {"Debit", "Credit", "Autopay Start", "Autopay End"};

///////////////////////////////////////////////
// local declarations
//
static void makeSzPenny(char * target, uint64_t pennies);
static void init_header(MPS7_HEADER *hdr);
static void init_summary(MPS7_SUMMARY *rec);

//////////////////////////////////////////////
// Data intake -> structs
//
/**
 *  Read the header.
 *  Returns # of bytes read, or -1 on a failure.
 */
int read_header (FILE *fp, MPS7_HEADER *header) {
	int out = 0;
	fread(header, LEN_HEADER, 1, fp);
	if (CLEAN_READ(fp)){
		header->record_count =  byteswap_32(header->record_count);
		printf("Header: version=[%u], records=[%u]\n",header->version, header->record_count);
	
		return sizeof(MPS7_HEADER);
	}
	else {
 	   fprintf(stderr,"Failed to read header, err=[%d] eof=[%d]\n",ferror(fp), feof(fp));
	   init_header(header);
	   return -1;
	}

	return out;
}

/**
 * Reads and validates the type of a record.  Optimistic read of base (autopay)
 * record.  If record is debit/credit, read the extra bytes into the amount.
 *
 * Populates [rec] with contents read from file;  initializes [rec] on a failure.
 *
 * Fails on bad file read or invalid record type.
 * Returns number of bytes read, -1 on a read failure, ERR_BAD_RECORD on an invalid record.
 */
int read_record(FILE *fp, MPS7_RECORD *rec) {
	int out = 0;

    init_rec(rec);
    rec->autopay.rec_type = fgetc(fp);

    fread(&(rec->autopay.rawTimestamp),1,sizeof(uint32_t),fp);
    fread(&(rec->autopay.userId),1,sizeof(uint64_t),fp);
    rec->autopay.rawTimestamp = byteswap_32(rec->autopay.rawTimestamp);
    rec->autopay.userId = byteswap_64(rec->autopay.userId);
    uint64_t amount = 0;

    if (CLEAN_READ(fp)) {
       switch (rec->autopay.rec_type) {
       case Debit:
       case Credit:
    	   fread(&amount,1,8,fp);
    	   uint64_t *temp = malloc(sizeof(uint64_t));
    	   uint64_t foo = byteswap_64(amount);
           if (convertFloatsTo754)
        	   ibm2double_numpy(temp, foo);
           else
        	   *temp = foo;
    	   memcpy(&(rec->debitCredit.amount),temp,sizeof(rec->debitCredit.amount));
    	   break;
       case StartAutoPay:
       case EndAutoPay:
    	   break;
       default:
    	   fprintf(stderr,"Invalid Record Found, recType=[%u]\n",rec->autopay.rec_type);
    	   init_rec(rec);
    	   return ERR_BAD_RECORD;
       }
    }
    else if (ferror(fp)) {
 	   fprintf(stderr,"Failed to read file, err=[%d] eof=[%d]\n",ferror(fp), feof(fp));
	   init_rec(rec);
	   return -1;
    }
	return out;
}


//////////////////////////////////////////////////////////
// Controllers...separate functions for separate contexts.
//

/**
 * Scans an MPS7 file, gathers file totals.  Complains if it reads a different # of records than header.
 * Aborts if a record is misread.
 */
MPS7_SUMMARY * mps7_file_summary(char *fname) {
	FILE *infile;
	MPS7_HEADER header;
	MPS7_RECORD current_record;
	MPS7_SUMMARY * out = (MPS7_SUMMARY *) malloc(sizeof(MPS7_SUMMARY));


	init_summary(out);
	unsigned int records_read = 0;
	int rc = 0;
	
	infile = fopen(fname,"rb");
	if (read_header(infile, &header) < 0) {
		out->status = ERR_BAD_HEADER;
		fclose(infile);
		return out;
	}
	
	do {
		rc = read_record(infile, &current_record);
		records_read++;
		accumulate_summary(out, current_record);

		if (CLEAN_READ(infile)) {
		  print_record(&current_record, records_read+1);
		  //print_summary(out);
		}
	} while (CLEAN_READ(infile) && rc != ERR_BAD_RECORD);

	set_endrun_status(out,ferror(infile), rc, header.record_count, records_read);
	fclose(infile);
	return out;
}

/**
 * Scans an MPS7 file, gathers totals for a given user.  Complains if it reads a different # of records than header.
 * Aborts if a record is misread.
 */
MPS7_USER_SUMMARY * mps7_user_summary(char *fname, uint64_t targetUser ) {
	FILE *infile;
	MPS7_HEADER header;
	MPS7_RECORD current_record;
	MPS7_USER_SUMMARY *out = malloc(sizeof(MPS7_USER_SUMMARY));

	init_summary(&(out->summary));
	out->userId = targetUser;

	uint32_t records_read = 0;
	int rc = 0;

	infile = fopen(fname,"rb");
	if (read_header(infile,&header) < 0) {
		out->summary.status = ERR_BAD_HEADER;
		fclose(infile);
		return out;
	}

	do {
		rc = read_record(infile, &current_record);
		records_read++;
		if (current_record.autopay.userId == targetUser)
			accumulate_summary(&(out->summary), current_record);
	}while (CLEAN_READ(infile) && rc != ERR_BAD_RECORD);

	set_endrun_status(&(out->summary), ferror(infile), rc, header.record_count, records_read);
	fclose(infile);
	return out;
}

////////////////////////////////////////////////////
// Distribution
//

/**
 * Sccumulates fields in a summary struct, corresponding to the record's
 * transaction type.
 */
void accumulate_summary(MPS7_SUMMARY *summary, MPS7_RECORD record) {
	switch(record.autopay.rec_type) {
	case StartAutoPay:
	   summary->qtyAutopayStart+=1;
	   break;
	case EndAutoPay:
		summary->qtyAutopayEnds+=1;
		break;
	case Credit:
//		fprintf(stderr, "\taccumulating %lf\n",record.debitCredit.amount);
		summary->creditTotalCents += TO_PENNIES(record.debitCredit.amount);
		break;
	case Debit:
//		fprintf(stderr, "\taccumulating %lf\n",record.debitCredit.amount);
		summary->debitTotalCents += TO_PENNIES(record.debitCredit.amount);
		break;
	}
}


///////////////////////////////////////////////////
// Outputs...
//
/**
 * formatted output for a summary struct.
 */
void print_summary(MPS7_SUMMARY *s) {
	formatMoney(s);
	printf("Total CR=[%s], Total DR[%s], Autopays: Starts=[%lu], Ends=[%lu]\n",
			s->szCreditAmount,
			s->szDebitAmount,
			s->qtyAutopayStart,
			s->qtyAutopayEnds);
}


/**
 * formatted output for a user.
 */
void print_user_credit_balance(MPS7_USER_SUMMARY *us) {
	char balance[LEN_CENTS_SZ];
        makeSzPenny(balance, NET_BALANCE_INT(us->summary.creditTotalCents, us->summary.debitTotalCents));
	formatMoney(&(us->summary));
	printf("Balance for user %llu = [%s].  (CR=[%s], DR=[%s])\n", us->userId, balance,
																us->summary.szCreditAmount,
																us->summary.szDebitAmount);
}

/**
 * output an MPS7 record
 */
void print_record(MPS7_RECORD *rec, int recNumber) {
//    printf("************\n");
    printf("Record #%d :  ", recNumber);
	switch(rec->autopay.rec_type ) {
	case Debit:
	case Credit:
		printf("type=[%s] date=[%lu] user=[%llu] amount=[%8.4lf]\n",
				recTypes[rec->autopay.rec_type],
				rec->autopay.rawTimestamp,
				rec->autopay.userId,
				rec->debitCredit.amount);
		break;
	case StartAutoPay:
	case EndAutoPay:
		printf("type=[%u] date=[%lu] user=[%llu]\n",
				recTypes[rec->autopay.rec_type],
				rec->autopay.rawTimestamp,
				rec->autopay.userId);
	}
}

/**
 * Wrapper for pre-print formatting of money strings.
 */
void formatMoney(MPS7_SUMMARY * s) {
	makeSzPenny(s->szCreditAmount, s->creditTotalCents);
	makeSzPenny(s->szDebitAmount, s->debitTotalCents);
}


/**
 * Quick-and-dirty money string formatter.
 */
static void makeSzPenny(char * target, uint64_t pennies) {
	//unsigned int cents = pennies % 100;
	//uint64_t  dollars = pennies / 100;
	if (pennies < 100) {
		sprintf(target, "0.%02lu",pennies);
	}
	else {
	        unsigned int cents = pennies % 100;
	        uint64_t  dollars = pennies / 100;
		sprintf(target, "%llu.%0u",dollars,cents);
	}
	return;
}


///////////////////////
// Utility
//

/**
 * Updates summary struct with post-processing status checks:
 * processing errors, I/O errors, record count mismatches vs. header.
 */
void set_endrun_status(MPS7_SUMMARY * out, int fileError, int returnCode,
					uint32_t expectedCount, uint32_t actualCount) {
	if (returnCode == ERR_BAD_RECORD) {
		init_summary(out);
		out->status = returnCode;
	}
	if (fileError) {
		init_summary(out);
		out->status = ERR_FILE_ERROR ;
	}

	if (expectedCount != actualCount) {
		fprintf(stderr, "Record count mismatch between file header and scan.  header:[%d],actual:[%d]\n", expectedCount, actualCount);
		out->status = ERR_RECORD_MISCOUNT;
	}
}

void init_header(MPS7_HEADER *hdr) {
	strncpy(hdr->format,MPS7_FORMAT,sizeof(hdr->format));
	hdr->record_count = 0;
	hdr->version = 0;
}

void init_rec(MPS7_RECORD *rec) {
	rec->autopay.rec_type = -1;
	rec->autopay.userId = 0;
	rec->autopay.rawTimestamp = 0;
	rec->debitCredit.amount = 0.0;
}

void init_summary(MPS7_SUMMARY *rec) {
	rec->status = 0;
	rec->creditTotalCents = 0;
	rec->debitTotalCents = 0;
	rec->qtyAutopayEnds = 0;
	rec->qtyAutopayStart = 0;
	memset(rec->szCreditAmount,'\0', sizeof(LEN_CENTS_SZ));
	memset(rec->szDebitAmount,'\0', sizeof(LEN_CENTS_SZ));
}

