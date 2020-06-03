/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_PUCCH_format0_H_
#define	_PUCCH_format0_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PUCCH-format0 */
typedef struct PUCCH_format0 {
	long	 initialCyclicShift;
	long	 nrofSymbols;
	long	 startingSymbolIndex;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PUCCH_format0_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PUCCH_format0;
extern asn_SEQUENCE_specifics_t asn_SPC_PUCCH_format0_specs_1;
extern asn_TYPE_member_t asn_MBR_PUCCH_format0_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _PUCCH_format0_H_ */
#include <asn_internal.h>
