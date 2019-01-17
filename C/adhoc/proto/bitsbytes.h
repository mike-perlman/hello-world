/*
 * bitsbytes.h
 *
 *  Created on: Jan 2, 2019
 *      Author: salience
 */

#ifndef SRC_BITSBYTES_H_
#define SRC_BITSBYTES_H_
uint64_t byteswap_64(uint64_t i);
uint32_t byteswap_32(uint32_t i);
void ibm2double_numpy (void * target,  uint64_t ibm);
#endif /* SRC_BITSBYTES_H_ */
