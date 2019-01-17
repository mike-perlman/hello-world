#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define IBM64_SIGN ((uint64_t)0x8000000000000000U)
#define IBM64_EXPT ((uint64_t)0x7f00000000000000U)
#define IBM64_FRAC ((uint64_t)0x00ffffffffffffffU)
#define IBM64_TOP  ((uint64_t)0x00f0000000000000U)
#define TIES_TO_EVEN_MASK64 ((uint64_t)0xfffffffffffffffd)
#define BITCOUNT_MAGIC ((uint32_t)0x000055afU)


uint32_t byteswap_32(uint32_t i) {
    uint32_t out = 0;
    out |= (i & 0xFF000000) >>24;
    out |= (i & 0x00FF0000) >>8;
    out |= (i & 0x0000FF00) <<8;
    out |= (i & 0x000000FF) <<24;
    return out;
}

uint64_t byteswap_64(uint64_t i) {
    uint64_t out = 0;
    out |= (i & 0xFF00000000000000) >>56;
    out |= (i & 0x00FF000000000000) >>40;
    out |= (i & 0x0000FF0000000000) >>24;
    out |= (i & 0x000000FF00000000) >>8;
    out |= (i & 0x00000000FF000000) <<8;
    out |= (i & 0x0000000000FF0000) <<24;
    out |= (i & 0x000000000000FF00) <<40;
    out |= (i & 0x00000000000000FF) <<56;
    return out;
}


/**
 * Adapted from Python:numPy's ibm2ieee package.  Converts
 * an 8-byte double-precision value from IBM to IEEE 754 format.
 */
void ibm2double_numpy (uint64_t * target,  uint64_t ibm) {
  uint64_t in = ibm;
  int inExp, outExp, leading_zeros;
  uint64_t inFrac, top_digit, outSign, outFrac, round_up;

  outSign = in & IBM64_SIGN;
  inFrac = in & IBM64_FRAC;
  if (!inFrac) {
	  target = 0; return;
  }

  inExp = (in & IBM64_EXPT) >> 54;

  top_digit = inFrac & IBM64_TOP;
  // printf("\t\ttop digit before:[%llx]...\n",top_digit);
  while (top_digit == 0) {
    inFrac <<= 4;
    inExp -= 4;
    top_digit = inFrac & IBM64_TOP;
  }
  // printf("\t\tafter:[%llx]...\n",top_digit);

  leading_zeros = (BITCOUNT_MAGIC >> (top_digit >> 51)) & 3U;

  // printf("\t\tleading_zeros:[%d]...\n",leading_zeros);
  inFrac <<= leading_zeros;
  outExp = inExp + 765 - leading_zeros;

  round_up = (inFrac & (uint64_t)0xb) > 0U;
  outFrac = ((inFrac >> 2) + round_up) >> 1;
  uint64_t out = (outSign + ((uint64_t)outExp << 52) + outFrac);
  memcpy(target, &out, sizeof(uint64_t));
  return;
}
