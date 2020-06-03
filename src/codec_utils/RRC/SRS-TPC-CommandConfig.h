/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_SRS_TPC_CommandConfig_H_
#define	_SRS_TPC_CommandConfig_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SRS-TPC-CommandConfig */
typedef struct SRS_TPC_CommandConfig {
	long	*startingBitOfFormat2_3;	/* OPTIONAL */
	long	*fieldTypeFormat2_3;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct SRS_TPC_CommandConfig__ext1 {
		long	*startingBitOfFormat2_3SUL_v1530;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext1;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SRS_TPC_CommandConfig_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SRS_TPC_CommandConfig;
extern asn_SEQUENCE_specifics_t asn_SPC_SRS_TPC_CommandConfig_specs_1;
extern asn_TYPE_member_t asn_MBR_SRS_TPC_CommandConfig_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _SRS_TPC_CommandConfig_H_ */
#include <asn_internal.h>
