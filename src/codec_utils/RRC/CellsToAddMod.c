/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "CellsToAddMod.h"

asn_TYPE_member_t asn_MBR_CellsToAddMod_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CellsToAddMod, physCellId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PhysCellId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"physCellId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CellsToAddMod, cellIndividualOffset),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Q_OffsetRangeList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cellIndividualOffset"
		},
};
static const ber_tlv_tag_t asn_DEF_CellsToAddMod_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_CellsToAddMod_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* physCellId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* cellIndividualOffset */
};
asn_SEQUENCE_specifics_t asn_SPC_CellsToAddMod_specs_1 = {
	sizeof(struct CellsToAddMod),
	offsetof(struct CellsToAddMod, _asn_ctx),
	asn_MAP_CellsToAddMod_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_CellsToAddMod = {
	"CellsToAddMod",
	"CellsToAddMod",
	&asn_OP_SEQUENCE,
	asn_DEF_CellsToAddMod_tags_1,
	sizeof(asn_DEF_CellsToAddMod_tags_1)
		/sizeof(asn_DEF_CellsToAddMod_tags_1[0]), /* 1 */
	asn_DEF_CellsToAddMod_tags_1,	/* Same as above */
	sizeof(asn_DEF_CellsToAddMod_tags_1)
		/sizeof(asn_DEF_CellsToAddMod_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_CellsToAddMod_1,
	2,	/* Elements count */
	&asn_SPC_CellsToAddMod_specs_1	/* Additional specs */
};

