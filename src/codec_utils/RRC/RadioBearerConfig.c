/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "RadioBearerConfig.h"

#include "SRB-ToAddModList.h"
#include "DRB-ToAddModList.h"
#include "DRB-ToReleaseList.h"
#include "SecurityConfig.h"
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_srb3_ToRelease_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_srb3_ToRelease_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_srb3_ToRelease_value2enum_3[] = {
	{ 0,	4,	"true" }
};
static const unsigned int asn_MAP_srb3_ToRelease_enum2value_3[] = {
	0	/* true(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_srb3_ToRelease_specs_3 = {
	asn_MAP_srb3_ToRelease_value2enum_3,	/* "tag" => N; sorted by tag */
	asn_MAP_srb3_ToRelease_enum2value_3,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_srb3_ToRelease_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_srb3_ToRelease_3 = {
	"srb3-ToRelease",
	"srb3-ToRelease",
	&asn_OP_NativeEnumerated,
	asn_DEF_srb3_ToRelease_tags_3,
	sizeof(asn_DEF_srb3_ToRelease_tags_3)
		/sizeof(asn_DEF_srb3_ToRelease_tags_3[0]) - 1, /* 1 */
	asn_DEF_srb3_ToRelease_tags_3,	/* Same as above */
	sizeof(asn_DEF_srb3_ToRelease_tags_3)
		/sizeof(asn_DEF_srb3_ToRelease_tags_3[0]), /* 2 */
	{ &asn_OER_type_srb3_ToRelease_constr_3, &asn_PER_type_srb3_ToRelease_constr_3, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_srb3_ToRelease_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_RadioBearerConfig_1[] = {
	{ ATF_POINTER, 5, offsetof(struct RadioBearerConfig, srb_ToAddModList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SRB_ToAddModList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"srb-ToAddModList"
		},
	{ ATF_POINTER, 4, offsetof(struct RadioBearerConfig, srb3_ToRelease),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_srb3_ToRelease_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"srb3-ToRelease"
		},
	{ ATF_POINTER, 3, offsetof(struct RadioBearerConfig, drb_ToAddModList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DRB_ToAddModList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"drb-ToAddModList"
		},
	{ ATF_POINTER, 2, offsetof(struct RadioBearerConfig, drb_ToReleaseList),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DRB_ToReleaseList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"drb-ToReleaseList"
		},
	{ ATF_POINTER, 1, offsetof(struct RadioBearerConfig, securityConfig),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SecurityConfig,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"securityConfig"
		},
};
static const int asn_MAP_RadioBearerConfig_oms_1[] = { 0, 1, 2, 3, 4 };
static const ber_tlv_tag_t asn_DEF_RadioBearerConfig_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RadioBearerConfig_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* srb-ToAddModList */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* srb3-ToRelease */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* drb-ToAddModList */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* drb-ToReleaseList */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* securityConfig */
};
asn_SEQUENCE_specifics_t asn_SPC_RadioBearerConfig_specs_1 = {
	sizeof(struct RadioBearerConfig),
	offsetof(struct RadioBearerConfig, _asn_ctx),
	asn_MAP_RadioBearerConfig_tag2el_1,
	5,	/* Count of tags in the map */
	asn_MAP_RadioBearerConfig_oms_1,	/* Optional members */
	5, 0,	/* Root/Additions */
	5,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RadioBearerConfig = {
	"RadioBearerConfig",
	"RadioBearerConfig",
	&asn_OP_SEQUENCE,
	asn_DEF_RadioBearerConfig_tags_1,
	sizeof(asn_DEF_RadioBearerConfig_tags_1)
		/sizeof(asn_DEF_RadioBearerConfig_tags_1[0]), /* 1 */
	asn_DEF_RadioBearerConfig_tags_1,	/* Same as above */
	sizeof(asn_DEF_RadioBearerConfig_tags_1)
		/sizeof(asn_DEF_RadioBearerConfig_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RadioBearerConfig_1,
	5,	/* Elements count */
	&asn_SPC_RadioBearerConfig_specs_1	/* Additional specs */
};

