/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_RRCResume_IEs_H_
#define	_RRCResume_IEs_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>
#include <NativeEnumerated.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRCResume_IEs__fullConfig {
	RRCResume_IEs__fullConfig_true	= 0
} e_RRCResume_IEs__fullConfig;

/* Forward declarations */
struct RadioBearerConfig;
struct MeasConfig;

/* RRCResume-IEs */
typedef struct RRCResume_IEs {
	struct RadioBearerConfig	*radioBearerConfig;	/* OPTIONAL */
	OCTET_STRING_t	*masterCellGroup;	/* OPTIONAL */
	struct MeasConfig	*measConfig;	/* OPTIONAL */
	long	*fullConfig;	/* OPTIONAL */
	OCTET_STRING_t	*lateNonCriticalExtension;	/* OPTIONAL */
	struct RRCResume_IEs__nonCriticalExtension {
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *nonCriticalExtension;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCResume_IEs_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_fullConfig_5;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_RRCResume_IEs;
extern asn_SEQUENCE_specifics_t asn_SPC_RRCResume_IEs_specs_1;
extern asn_TYPE_member_t asn_MBR_RRCResume_IEs_1[6];

#ifdef __cplusplus
}
#endif

#endif	/* _RRCResume_IEs_H_ */
#include <asn_internal.h>
