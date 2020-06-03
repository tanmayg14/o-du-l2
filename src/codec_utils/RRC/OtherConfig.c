/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "OtherConfig.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_delayBudgetReportingProhibitTimer_constr_5 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_delayBudgetReportingProhibitTimer_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_delayBudgetReportingConfig_constr_2 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_delayBudgetReportingConfig_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_delayBudgetReportingProhibitTimer_value2enum_5[] = {
	{ 0,	2,	"s0" },
	{ 1,	6,	"s0dot4" },
	{ 2,	6,	"s0dot8" },
	{ 3,	6,	"s1dot6" },
	{ 4,	2,	"s3" },
	{ 5,	2,	"s6" },
	{ 6,	3,	"s12" },
	{ 7,	3,	"s30" }
};
static const unsigned int asn_MAP_delayBudgetReportingProhibitTimer_enum2value_5[] = {
	0,	/* s0(0) */
	1,	/* s0dot4(1) */
	2,	/* s0dot8(2) */
	6,	/* s12(6) */
	3,	/* s1dot6(3) */
	4,	/* s3(4) */
	7,	/* s30(7) */
	5	/* s6(5) */
};
static const asn_INTEGER_specifics_t asn_SPC_delayBudgetReportingProhibitTimer_specs_5 = {
	asn_MAP_delayBudgetReportingProhibitTimer_value2enum_5,	/* "tag" => N; sorted by tag */
	asn_MAP_delayBudgetReportingProhibitTimer_enum2value_5,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_delayBudgetReportingProhibitTimer_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_delayBudgetReportingProhibitTimer_5 = {
	"delayBudgetReportingProhibitTimer",
	"delayBudgetReportingProhibitTimer",
	&asn_OP_NativeEnumerated,
	asn_DEF_delayBudgetReportingProhibitTimer_tags_5,
	sizeof(asn_DEF_delayBudgetReportingProhibitTimer_tags_5)
		/sizeof(asn_DEF_delayBudgetReportingProhibitTimer_tags_5[0]) - 1, /* 1 */
	asn_DEF_delayBudgetReportingProhibitTimer_tags_5,	/* Same as above */
	sizeof(asn_DEF_delayBudgetReportingProhibitTimer_tags_5)
		/sizeof(asn_DEF_delayBudgetReportingProhibitTimer_tags_5[0]), /* 2 */
	{ &asn_OER_type_delayBudgetReportingProhibitTimer_constr_5, &asn_PER_type_delayBudgetReportingProhibitTimer_constr_5, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_delayBudgetReportingProhibitTimer_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_setup_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct OtherConfig__delayBudgetReportingConfig__setup, delayBudgetReportingProhibitTimer),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_delayBudgetReportingProhibitTimer_5,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"delayBudgetReportingProhibitTimer"
		},
};
static const ber_tlv_tag_t asn_DEF_setup_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_setup_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* delayBudgetReportingProhibitTimer */
};
static asn_SEQUENCE_specifics_t asn_SPC_setup_specs_4 = {
	sizeof(struct OtherConfig__delayBudgetReportingConfig__setup),
	offsetof(struct OtherConfig__delayBudgetReportingConfig__setup, _asn_ctx),
	asn_MAP_setup_tag2el_4,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_setup_4 = {
	"setup",
	"setup",
	&asn_OP_SEQUENCE,
	asn_DEF_setup_tags_4,
	sizeof(asn_DEF_setup_tags_4)
		/sizeof(asn_DEF_setup_tags_4[0]) - 1, /* 1 */
	asn_DEF_setup_tags_4,	/* Same as above */
	sizeof(asn_DEF_setup_tags_4)
		/sizeof(asn_DEF_setup_tags_4[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_setup_4,
	1,	/* Elements count */
	&asn_SPC_setup_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_delayBudgetReportingConfig_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct OtherConfig__delayBudgetReportingConfig, choice.release),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"release"
		},
	{ ATF_POINTER, 0, offsetof(struct OtherConfig__delayBudgetReportingConfig, choice.setup),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_setup_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setup"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_delayBudgetReportingConfig_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* release */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* setup */
};
static asn_CHOICE_specifics_t asn_SPC_delayBudgetReportingConfig_specs_2 = {
	sizeof(struct OtherConfig__delayBudgetReportingConfig),
	offsetof(struct OtherConfig__delayBudgetReportingConfig, _asn_ctx),
	offsetof(struct OtherConfig__delayBudgetReportingConfig, present),
	sizeof(((struct OtherConfig__delayBudgetReportingConfig *)0)->present),
	asn_MAP_delayBudgetReportingConfig_tag2el_2,
	2,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_delayBudgetReportingConfig_2 = {
	"delayBudgetReportingConfig",
	"delayBudgetReportingConfig",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_delayBudgetReportingConfig_constr_2, &asn_PER_type_delayBudgetReportingConfig_constr_2, CHOICE_constraint },
	asn_MBR_delayBudgetReportingConfig_2,
	2,	/* Elements count */
	&asn_SPC_delayBudgetReportingConfig_specs_2	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_OtherConfig_1[] = {
	{ ATF_POINTER, 1, offsetof(struct OtherConfig, delayBudgetReportingConfig),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_delayBudgetReportingConfig_2,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"delayBudgetReportingConfig"
		},
};
static const int asn_MAP_OtherConfig_oms_1[] = { 0 };
static const ber_tlv_tag_t asn_DEF_OtherConfig_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_OtherConfig_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* delayBudgetReportingConfig */
};
asn_SEQUENCE_specifics_t asn_SPC_OtherConfig_specs_1 = {
	sizeof(struct OtherConfig),
	offsetof(struct OtherConfig, _asn_ctx),
	asn_MAP_OtherConfig_tag2el_1,
	1,	/* Count of tags in the map */
	asn_MAP_OtherConfig_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_OtherConfig = {
	"OtherConfig",
	"OtherConfig",
	&asn_OP_SEQUENCE,
	asn_DEF_OtherConfig_tags_1,
	sizeof(asn_DEF_OtherConfig_tags_1)
		/sizeof(asn_DEF_OtherConfig_tags_1[0]), /* 1 */
	asn_DEF_OtherConfig_tags_1,	/* Same as above */
	sizeof(asn_DEF_OtherConfig_tags_1)
		/sizeof(asn_DEF_OtherConfig_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_OtherConfig_1,
	1,	/* Elements count */
	&asn_SPC_OtherConfig_specs_1	/* Additional specs */
};

