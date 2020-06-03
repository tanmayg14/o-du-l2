/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_SlotFormatCombinationsPerCell_H_
#define	_SlotFormatCombinationsPerCell_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ServCellIndex.h"
#include "SubcarrierSpacing.h"
#include <NativeInteger.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SlotFormatCombination;

/* SlotFormatCombinationsPerCell */
typedef struct SlotFormatCombinationsPerCell {
	ServCellIndex_t	 servingCellId;
	SubcarrierSpacing_t	 subcarrierSpacing;
	SubcarrierSpacing_t	*subcarrierSpacing2;	/* OPTIONAL */
	struct SlotFormatCombinationsPerCell__slotFormatCombinations {
		A_SEQUENCE_OF(struct SlotFormatCombination) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *slotFormatCombinations;
	long	*positionInDCI;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SlotFormatCombinationsPerCell_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SlotFormatCombinationsPerCell;
extern asn_SEQUENCE_specifics_t asn_SPC_SlotFormatCombinationsPerCell_specs_1;
extern asn_TYPE_member_t asn_MBR_SlotFormatCombinationsPerCell_1[5];

#ifdef __cplusplus
}
#endif

#endif	/* _SlotFormatCombinationsPerCell_H_ */
#include <asn_internal.h>
