#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "./mps7.h"

#define TARGET_USER	                       2456938384156277127
#define TARGET_FILE                        "txnlog.dat"
#define OPT_SWAP_FLOATS                    "ieeefp"
extern int convertFloatsTo754;

int main (int argc, char *argv[]) {

	if (argc > 1 && !strncmp(argv[1],OPT_SWAP_FLOATS,sizeof(OPT_SWAP_FLOATS)))
		convertFloatsTo754 = 1;
	else
		convertFloatsTo754 = 0;

	uint64_t targetId = TARGET_USER;

	MPS7_SUMMARY *fileSummary = mps7_file_summary(TARGET_FILE);
	MPS7_USER_SUMMARY *userSummary = mps7_user_summary(TARGET_FILE, targetId);

	if (convertFloatsTo754)
		printf("IBM -> IEEE-754 conversion enabled.\n");
	else
		printf("Disabled IBM -> IEEE-754 conversion.\n");

	print_summary(fileSummary);
	printf("*******\nGathering xacts for user [%llu].\n",targetId);
	print_user_credit_balance(userSummary);

	if (fileSummary->status < 0){
	  printf("Errors detected in file summary.  Exiting with code [%d].\n", fileSummary->status);
          return fileSummary->status;
        }

	if (userSummary->summary.status < 0) {
	  printf("Errors detected in user summary.  Exiting with code [%d].\n", userSummary->summary.status);
          return userSummary->summary.status;
        }

	return 0;
}
