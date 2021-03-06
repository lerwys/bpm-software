#ifndef _ACQ_CHAN_H_
#define _ACQ_CHAN_H_

#define BLOCK_SIZE 131072

/* ADC */
#define ADC_CHAN_ID 0
#define ADC_SAMPLE_SIZE 8 // 8 Bytes -> ADC0 = 16-bit / ADC1 = 16-bit ...

/* TBT AMP */
#define TBTAMP_CHAN_ID 1
#define TBTAMP_SAMPLE_SIZE 16 // 16 Bytes -> TBTAMP0 = 32-bit / TBTAMP1 = 32-bit ...

/* TBT POS */
#define TBTPOS_CHAN_ID 2
#define TBTPOS_SAMPLE_SIZE 16 // 16 Bytes -> X = 32-bit / Y = 32-bit ...

/* FOFB AMP */
#define FOFBAMP_CHAN_ID 3
#define FOFBAMP_SAMPLE_SIZE 16 // 16 Bytes -> FOFBAMP0 = 32-bit / FOFBAMP1 = 32-bit ...

/* FOFB POS */
#define FOFBPOS_CHAN_ID 4
#define FOFBPOS_SAMPLE_SIZE 16 // 16 Bytes -> X = 32-bit / Y = 32-bit ...

#define END_CHAN_ID 5

#endif

