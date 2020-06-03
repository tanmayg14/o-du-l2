/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "SI-RequestConfig.h"

#include "SI-RequestResources.h"
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static int
memb_si_RequestResources_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	/* Determine the number of elements */
	size = _A_CSEQUENCE_FROM_VOID(sptr)->count;
	
	if((size >= 1 && size <= 32)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_ssb_perRACH_Occasion_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_ssb_perRACH_Occasion_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_si_RequestPeriod_constr_13 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_si_RequestPeriod_constr_13 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_si_RequestResources_constr_22 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..32)) */};
static asn_per_constraints_t asn_PER_type_si_RequestResources_constr_22 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_si_RequestResources_constr_22 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..32)) */};
static asn_per_constraints_t asn_PER_memb_si_RequestResources_constr_22 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_ssb_perRACH_Occasion_value2enum_4[] = {
	{ 0,	9,	"oneEighth" },
	{ 1,	9,	"oneFourth" },
	{ 2,	7,	"oneHalf" },
	{ 3,	3,	"one" },
	{ 4,	3,	"two" },
	{ 5,	4,	"four" },
	{ 6,	5,	"eight" },
	{ 7,	7,	"sixteen" }
};
static const unsigned int asn_MAP_ssb_perRACH_Occasion_enum2value_4[] = {
	6,	/* eight(6) */
	5,	/* four(5) */
	3,	/* one(3) */
	0,	/* oneEighth(0) */
	1,	/* oneFourth(1) */
	2,	/* oneHalf(2) */
	7,	/* sixteen(7) */
	4	/* two(4) */
};
static const asn_INTEGER_specifics_t asn_SPC_ssb_perRACH_Occasion_specs_4 = {
	asn_MAP_ssb_perRACH_Occasion_value2enum_4,	/* "tag" => N; sorted by tag */
	asn_MAP_ssb_perRACH_Occasion_enum2value_4,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_ssb_perRACH_Occasion_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ssb_perRACH_Occasion_4 = {
	"ssb-perRACH-Occasion",
	"ssb-perRACH-Occasion",
	&asn_OP_NativeEnumerated,
	asn_DEF_ssb_perRACH_Occasion_tags_4,
	sizeof(asn_DEF_ssb_perRACH_Occasion_tags_4)
		/sizeof(asn_DEF_ssb_perRACH_Occasion_tags_4[0]) - 1, /* 1 */
	asn_DEF_ssb_perRACH_Occasion_tags_4,	/* Same as above */
	sizeof(asn_DEF_ssb_perRACH_Occasion_tags_4)
		/sizeof(asn_DEF_ssb_perRACH_Occasion_tags_4[0]), /* 2 */
	{ &asn_OER_type_ssb_perRACH_Occasion_constr_4, &asn_PER_type_ssb_perRACH_Occasion_constr_4, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_ssb_perRACH_Occasion_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_rach_OccasionsSI_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SI_RequestConfig__rach_OccasionsSI, rach_ConfigSI),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RACH_ConfigGeneric,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rach-ConfigSI"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SI_RequestConfig__rach_OccasionsSI, ssb_perRACH_Occasion),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ssb_perRACH_Occasion_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ssb-perRACH-Occasion"
		},
};
static const ber_tlv_tag_t asn_DEF_rach_OccasionsSI_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_rach_OccasionsSI_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rach-ConfigSI */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* ssb-perRACH-Occasion */
};
static asn_SEQUENCE_specifics_t asn_SPC_rach_OccasionsSI_specs_2 = {
	sizeof(struct SI_RequestConfig__rach_OccasionsSI),
	offsetof(struct SI_RequestConfig__rach_OccasionsSI, _asn_ctx),
	asn_MAP_rach_OccasionsSI_tag2el_2,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_rach_OccasionsSI_2 = {
	"rach-OccasionsSI",
	"rach-OccasionsSI",
	&asn_OP_SEQUENCE,
	asn_DEF_rach_OccasionsSI_tags_2,
	sizeof(asn_DEF_rach_OccasionsSI_tags_2)
		/sizeof(asn_DEF_rach_OccasionsSI_tags_2[0]) - 1, /* 1 */
	asn_DEF_rach_OccasionsSI_tags_2,	/* Same as above */
	sizeof(asn_DEF_rach_OccasionsSI_tags_2)
		/sizeof(asn_DEF_rach_OccasionsSI_tags_2[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_rach_OccasionsSI_2,
	2,	/* Elements count */
	&asn_SPC_rach_OccasionsSI_specs_2	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_si_RequestPeriod_value2enum_13[] = {
	{ 0,	3,	"one" },
	{ 1,	3,	"two" },
	{ 2,	4,	"four" },
	{ 3,	3,	"six" },
	{ 4,	5,	"eight" },
	{ 5,	3,	"ten" },
	{ 6,	6,	"twelve" },
	{ 7,	7,	"sixteen" }
};
static const unsigned int asn_MAP_si_RequestPeriod_enum2value_13[] = {
	4,	/* eight(4) */
	2,	/* four(2) */
	0,	/* one(0) */
	3,	/* six(3) */
	7,	/* sixteen(7) */
	5,	/* ten(5) */
	6,	/* twelve(6) */
	1	/* two(1) */
};
static const asn_INTEGER_specifics_t asn_SPC_si_RequestPeriod_specs_13 = {
	asn_MAP_si_RequestPeriod_value2enum_13,	/* "tag" => N; sorted by tag */
	asn_MAP_si_RequestPeriod_enum2value_13,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_si_RequestPeriod_tags_13[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_si_RequestPeriod_13 = {
	"si-RequestPeriod",
	"si-RequestPeriod",
	&asn_OP_NativeEnumerated,
	asn_DEF_si_RequestPeriod_tags_13,
	sizeof(asn_DEF_si_RequestPeriod_tags_13)
		/sizeof(asn_DEF_si_RequestPeriod_tags_13[0]) - 1, /* 1 */
	asn_DEF_si_RequestPeriod_tags_13,	/* Same as above */
	sizeof(asn_DEF_si_RequestPeriod_tags_13)
		/sizeof(asn_DEF_si_RequestPeriod_tags_13[0]), /* 2 */
	{ &asn_OER_type_si_RequestPeriod_constr_13, &asn_PER_type_si_RequestPeriod_constr_13, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_si_RequestPeriod_specs_13	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_si_RequestResources_22[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_SI_RequestResources,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_si_RequestResources_tags_22[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_si_RequestResources_specs_22 = {
	sizeof(struct SI_RequestConfig__si_RequestResources),
	offsetof(struct SI_RequestConfig__si_RequestResources, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_si_RequestResources_22 = {
	"si-RequestResources",
	"si-RequestResources",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_si_RequestResources_tags_22,
	sizeof(asn_DEF_si_RequestResources_tags_22)
		/sizeof(asn_DEF_si_RequestResources_tags_22[0]) - 1, /* 1 */
	asn_DEF_si_RequestResources_tags_22,	/* Same as above */
	sizeof(asn_DEF_si_RequestResources_tags_22)
		/sizeof(asn_DEF_si_RequestResources_tags_22[0]), /* 2 */
	{ &asn_OER_type_si_RequestResources_constr_22, &asn_PER_type_si_RequestResources_constr_22, SEQUENCE_OF_constraint },
	asn_MBR_si_RequestResources_22,
	1,	/* Single element */
	&asn_SPC_si_RequestResources_specs_22	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_SI_RequestConfig_1[] = {
	{ ATF_POINTER, 2, offsetof(struct SI_RequestConfig, rach_OccasionsSI),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_rach_OccasionsSI_2,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rach-OccasionsSI"
		},
	{ ATF_POINTER, 1, offsetof(struct SI_RequestConfig, si_RequestPeriod),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_si_RequestPeriod_13,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"si-RequestPeriod"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SI_RequestConfig, si_RequestResources),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_si_RequestResources_22,
		0,
		{ &asn_OER_memb_si_RequestResources_constr_22, &asn_PER_memb_si_RequestResources_constr_22,  memb_si_RequestResources_constraint_1 },
		0, 0, /* No default value */
		"si-RequestResources"
		},
};
static const int asn_MAP_SI_RequestConfig_oms_1[] = { 0, 1 };
static const ber_tlv_tag_t asn_DEF_SI_RequestConfig_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SI_RequestConfig_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rach-OccasionsSI */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* si-RequestPeriod */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* si-RequestResources */
};
asn_SEQUENCE_specifics_t asn_SPC_SI_RequestConfig_specs_1 = {
	sizeof(struct SI_RequestConfig),
	offsetof(struct SI_RequestConfig, _asn_ctx),
	asn_MAP_SI_RequestConfig_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_SI_RequestConfig_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SI_RequestConfig = {
	"SI-RequestConfig",
	"SI-RequestConfig",
	&asn_OP_SEQUENCE,
	asn_DEF_SI_RequestConfig_tags_1,
	sizeof(asn_DEF_SI_RequestConfig_tags_1)
		/sizeof(asn_DEF_SI_RequestConfig_tags_1[0]), /* 1 */
	asn_DEF_SI_RequestConfig_tags_1,	/* Same as above */
	sizeof(asn_DEF_SI_RequestConfig_tags_1)
		/sizeof(asn_DEF_SI_RequestConfig_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SI_RequestConfig_1,
	3,	/* Elements count */
	&asn_SPC_SI_RequestConfig_specs_1	/* Additional specs */
};

