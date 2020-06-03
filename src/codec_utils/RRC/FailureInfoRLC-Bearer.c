/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "FailureInfoRLC-Bearer.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_failureType_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_failureType_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_failureType_value2enum_4[] = {
	{ 0,	11,	"duplication" },
	{ 1,	6,	"spare3" },
	{ 2,	6,	"spare2" },
	{ 3,	6,	"spare1" }
};
static const unsigned int asn_MAP_failureType_enum2value_4[] = {
	0,	/* duplication(0) */
	3,	/* spare1(3) */
	2,	/* spare2(2) */
	1	/* spare3(1) */
};
static const asn_INTEGER_specifics_t asn_SPC_failureType_specs_4 = {
	asn_MAP_failureType_value2enum_4,	/* "tag" => N; sorted by tag */
	asn_MAP_failureType_enum2value_4,	/* N => "tag"; sorted by N */
	4,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_failureType_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_failureType_4 = {
	"failureType",
	"failureType",
	&asn_OP_NativeEnumerated,
	asn_DEF_failureType_tags_4,
	sizeof(asn_DEF_failureType_tags_4)
		/sizeof(asn_DEF_failureType_tags_4[0]) - 1, /* 1 */
	asn_DEF_failureType_tags_4,	/* Same as above */
	sizeof(asn_DEF_failureType_tags_4)
		/sizeof(asn_DEF_failureType_tags_4[0]), /* 2 */
	{ &asn_OER_type_failureType_constr_4, &asn_PER_type_failureType_constr_4, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_failureType_specs_4	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_FailureInfoRLC_Bearer_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct FailureInfoRLC_Bearer, cellGroupId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellGroupId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cellGroupId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FailureInfoRLC_Bearer, logicalChannelIdentity),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LogicalChannelIdentity,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"logicalChannelIdentity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FailureInfoRLC_Bearer, failureType),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_failureType_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"failureType"
		},
};
static const ber_tlv_tag_t asn_DEF_FailureInfoRLC_Bearer_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_FailureInfoRLC_Bearer_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* cellGroupId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* logicalChannelIdentity */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* failureType */
};
asn_SEQUENCE_specifics_t asn_SPC_FailureInfoRLC_Bearer_specs_1 = {
	sizeof(struct FailureInfoRLC_Bearer),
	offsetof(struct FailureInfoRLC_Bearer, _asn_ctx),
	asn_MAP_FailureInfoRLC_Bearer_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_FailureInfoRLC_Bearer = {
	"FailureInfoRLC-Bearer",
	"FailureInfoRLC-Bearer",
	&asn_OP_SEQUENCE,
	asn_DEF_FailureInfoRLC_Bearer_tags_1,
	sizeof(asn_DEF_FailureInfoRLC_Bearer_tags_1)
		/sizeof(asn_DEF_FailureInfoRLC_Bearer_tags_1[0]), /* 1 */
	asn_DEF_FailureInfoRLC_Bearer_tags_1,	/* Same as above */
	sizeof(asn_DEF_FailureInfoRLC_Bearer_tags_1)
		/sizeof(asn_DEF_FailureInfoRLC_Bearer_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_FailureInfoRLC_Bearer_1,
	3,	/* Elements count */
	&asn_SPC_FailureInfoRLC_Bearer_specs_1	/* Additional specs */
};

