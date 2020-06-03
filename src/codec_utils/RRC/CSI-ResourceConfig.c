/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "CSI-ResourceConfig.h"

static int
memb_nzp_CSI_RS_ResourceSetList_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 1 && size <= 16)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_csi_SSB_ResourceSetList_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 1)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_csi_IM_ResourceSetList_constraint_3(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 1 && size <= 16)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_nzp_CSI_RS_ResourceSetList_constr_5 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..16)) */};
static asn_per_constraints_t asn_PER_type_nzp_CSI_RS_ResourceSetList_constr_5 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  1,  16 }	/* (SIZE(1..16)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_csi_SSB_ResourceSetList_constr_7 CC_NOTUSED = {
	{ 0, 0 },
	1	/* (SIZE(1..1)) */};
static asn_per_constraints_t asn_PER_type_csi_SSB_ResourceSetList_constr_7 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  1,  1 }	/* (SIZE(1..1)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_nzp_CSI_RS_ResourceSetList_constr_5 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..16)) */};
static asn_per_constraints_t asn_PER_memb_nzp_CSI_RS_ResourceSetList_constr_5 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  1,  16 }	/* (SIZE(1..16)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_csi_SSB_ResourceSetList_constr_7 CC_NOTUSED = {
	{ 0, 0 },
	1	/* (SIZE(1..1)) */};
static asn_per_constraints_t asn_PER_memb_csi_SSB_ResourceSetList_constr_7 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  1,  1 }	/* (SIZE(1..1)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_csi_IM_ResourceSetList_constr_9 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..16)) */};
static asn_per_constraints_t asn_PER_type_csi_IM_ResourceSetList_constr_9 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  1,  16 }	/* (SIZE(1..16)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_csi_IM_ResourceSetList_constr_9 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..16)) */};
static asn_per_constraints_t asn_PER_memb_csi_IM_ResourceSetList_constr_9 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  1,  16 }	/* (SIZE(1..16)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_csi_RS_ResourceSetList_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_csi_RS_ResourceSetList_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_resourceType_constr_12 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_resourceType_constr_12 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_nzp_CSI_RS_ResourceSetList_5[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NZP_CSI_RS_ResourceSetId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_nzp_CSI_RS_ResourceSetList_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_nzp_CSI_RS_ResourceSetList_specs_5 = {
	sizeof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__nzp_CSI_RS_SSB__nzp_CSI_RS_ResourceSetList),
	offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__nzp_CSI_RS_SSB__nzp_CSI_RS_ResourceSetList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nzp_CSI_RS_ResourceSetList_5 = {
	"nzp-CSI-RS-ResourceSetList",
	"nzp-CSI-RS-ResourceSetList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_nzp_CSI_RS_ResourceSetList_tags_5,
	sizeof(asn_DEF_nzp_CSI_RS_ResourceSetList_tags_5)
		/sizeof(asn_DEF_nzp_CSI_RS_ResourceSetList_tags_5[0]) - 1, /* 1 */
	asn_DEF_nzp_CSI_RS_ResourceSetList_tags_5,	/* Same as above */
	sizeof(asn_DEF_nzp_CSI_RS_ResourceSetList_tags_5)
		/sizeof(asn_DEF_nzp_CSI_RS_ResourceSetList_tags_5[0]), /* 2 */
	{ &asn_OER_type_nzp_CSI_RS_ResourceSetList_constr_5, &asn_PER_type_nzp_CSI_RS_ResourceSetList_constr_5, SEQUENCE_OF_constraint },
	asn_MBR_nzp_CSI_RS_ResourceSetList_5,
	1,	/* Single element */
	&asn_SPC_nzp_CSI_RS_ResourceSetList_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_csi_SSB_ResourceSetList_7[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_CSI_SSB_ResourceSetId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_csi_SSB_ResourceSetList_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_csi_SSB_ResourceSetList_specs_7 = {
	sizeof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__nzp_CSI_RS_SSB__csi_SSB_ResourceSetList),
	offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__nzp_CSI_RS_SSB__csi_SSB_ResourceSetList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_csi_SSB_ResourceSetList_7 = {
	"csi-SSB-ResourceSetList",
	"csi-SSB-ResourceSetList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_csi_SSB_ResourceSetList_tags_7,
	sizeof(asn_DEF_csi_SSB_ResourceSetList_tags_7)
		/sizeof(asn_DEF_csi_SSB_ResourceSetList_tags_7[0]) - 1, /* 1 */
	asn_DEF_csi_SSB_ResourceSetList_tags_7,	/* Same as above */
	sizeof(asn_DEF_csi_SSB_ResourceSetList_tags_7)
		/sizeof(asn_DEF_csi_SSB_ResourceSetList_tags_7[0]), /* 2 */
	{ &asn_OER_type_csi_SSB_ResourceSetList_constr_7, &asn_PER_type_csi_SSB_ResourceSetList_constr_7, SEQUENCE_OF_constraint },
	asn_MBR_csi_SSB_ResourceSetList_7,
	1,	/* Single element */
	&asn_SPC_csi_SSB_ResourceSetList_specs_7	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_nzp_CSI_RS_SSB_4[] = {
	{ ATF_POINTER, 2, offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__nzp_CSI_RS_SSB, nzp_CSI_RS_ResourceSetList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_nzp_CSI_RS_ResourceSetList_5,
		0,
		{ &asn_OER_memb_nzp_CSI_RS_ResourceSetList_constr_5, &asn_PER_memb_nzp_CSI_RS_ResourceSetList_constr_5,  memb_nzp_CSI_RS_ResourceSetList_constraint_4 },
		0, 0, /* No default value */
		"nzp-CSI-RS-ResourceSetList"
		},
	{ ATF_POINTER, 1, offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__nzp_CSI_RS_SSB, csi_SSB_ResourceSetList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_csi_SSB_ResourceSetList_7,
		0,
		{ &asn_OER_memb_csi_SSB_ResourceSetList_constr_7, &asn_PER_memb_csi_SSB_ResourceSetList_constr_7,  memb_csi_SSB_ResourceSetList_constraint_4 },
		0, 0, /* No default value */
		"csi-SSB-ResourceSetList"
		},
};
static const int asn_MAP_nzp_CSI_RS_SSB_oms_4[] = { 0, 1 };
static const ber_tlv_tag_t asn_DEF_nzp_CSI_RS_SSB_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_nzp_CSI_RS_SSB_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* nzp-CSI-RS-ResourceSetList */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* csi-SSB-ResourceSetList */
};
static asn_SEQUENCE_specifics_t asn_SPC_nzp_CSI_RS_SSB_specs_4 = {
	sizeof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__nzp_CSI_RS_SSB),
	offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__nzp_CSI_RS_SSB, _asn_ctx),
	asn_MAP_nzp_CSI_RS_SSB_tag2el_4,
	2,	/* Count of tags in the map */
	asn_MAP_nzp_CSI_RS_SSB_oms_4,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nzp_CSI_RS_SSB_4 = {
	"nzp-CSI-RS-SSB",
	"nzp-CSI-RS-SSB",
	&asn_OP_SEQUENCE,
	asn_DEF_nzp_CSI_RS_SSB_tags_4,
	sizeof(asn_DEF_nzp_CSI_RS_SSB_tags_4)
		/sizeof(asn_DEF_nzp_CSI_RS_SSB_tags_4[0]) - 1, /* 1 */
	asn_DEF_nzp_CSI_RS_SSB_tags_4,	/* Same as above */
	sizeof(asn_DEF_nzp_CSI_RS_SSB_tags_4)
		/sizeof(asn_DEF_nzp_CSI_RS_SSB_tags_4[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_nzp_CSI_RS_SSB_4,
	2,	/* Elements count */
	&asn_SPC_nzp_CSI_RS_SSB_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_csi_IM_ResourceSetList_9[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_CSI_IM_ResourceSetId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_csi_IM_ResourceSetList_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_csi_IM_ResourceSetList_specs_9 = {
	sizeof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__csi_IM_ResourceSetList),
	offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList__csi_IM_ResourceSetList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_csi_IM_ResourceSetList_9 = {
	"csi-IM-ResourceSetList",
	"csi-IM-ResourceSetList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_csi_IM_ResourceSetList_tags_9,
	sizeof(asn_DEF_csi_IM_ResourceSetList_tags_9)
		/sizeof(asn_DEF_csi_IM_ResourceSetList_tags_9[0]) - 1, /* 1 */
	asn_DEF_csi_IM_ResourceSetList_tags_9,	/* Same as above */
	sizeof(asn_DEF_csi_IM_ResourceSetList_tags_9)
		/sizeof(asn_DEF_csi_IM_ResourceSetList_tags_9[0]), /* 2 */
	{ &asn_OER_type_csi_IM_ResourceSetList_constr_9, &asn_PER_type_csi_IM_ResourceSetList_constr_9, SEQUENCE_OF_constraint },
	asn_MBR_csi_IM_ResourceSetList_9,
	1,	/* Single element */
	&asn_SPC_csi_IM_ResourceSetList_specs_9	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_csi_RS_ResourceSetList_3[] = {
	{ ATF_POINTER, 0, offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList, choice.nzp_CSI_RS_SSB),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_nzp_CSI_RS_SSB_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"nzp-CSI-RS-SSB"
		},
	{ ATF_POINTER, 0, offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList, choice.csi_IM_ResourceSetList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_csi_IM_ResourceSetList_9,
		0,
		{ &asn_OER_memb_csi_IM_ResourceSetList_constr_9, &asn_PER_memb_csi_IM_ResourceSetList_constr_9,  memb_csi_IM_ResourceSetList_constraint_3 },
		0, 0, /* No default value */
		"csi-IM-ResourceSetList"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_csi_RS_ResourceSetList_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* nzp-CSI-RS-SSB */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* csi-IM-ResourceSetList */
};
static asn_CHOICE_specifics_t asn_SPC_csi_RS_ResourceSetList_specs_3 = {
	sizeof(struct CSI_ResourceConfig__csi_RS_ResourceSetList),
	offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList, _asn_ctx),
	offsetof(struct CSI_ResourceConfig__csi_RS_ResourceSetList, present),
	sizeof(((struct CSI_ResourceConfig__csi_RS_ResourceSetList *)0)->present),
	asn_MAP_csi_RS_ResourceSetList_tag2el_3,
	2,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_csi_RS_ResourceSetList_3 = {
	"csi-RS-ResourceSetList",
	"csi-RS-ResourceSetList",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_csi_RS_ResourceSetList_constr_3, &asn_PER_type_csi_RS_ResourceSetList_constr_3, CHOICE_constraint },
	asn_MBR_csi_RS_ResourceSetList_3,
	2,	/* Elements count */
	&asn_SPC_csi_RS_ResourceSetList_specs_3	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_resourceType_value2enum_12[] = {
	{ 0,	9,	"aperiodic" },
	{ 1,	14,	"semiPersistent" },
	{ 2,	8,	"periodic" }
};
static const unsigned int asn_MAP_resourceType_enum2value_12[] = {
	0,	/* aperiodic(0) */
	2,	/* periodic(2) */
	1	/* semiPersistent(1) */
};
static const asn_INTEGER_specifics_t asn_SPC_resourceType_specs_12 = {
	asn_MAP_resourceType_value2enum_12,	/* "tag" => N; sorted by tag */
	asn_MAP_resourceType_enum2value_12,	/* N => "tag"; sorted by N */
	3,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_resourceType_tags_12[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_resourceType_12 = {
	"resourceType",
	"resourceType",
	&asn_OP_NativeEnumerated,
	asn_DEF_resourceType_tags_12,
	sizeof(asn_DEF_resourceType_tags_12)
		/sizeof(asn_DEF_resourceType_tags_12[0]) - 1, /* 1 */
	asn_DEF_resourceType_tags_12,	/* Same as above */
	sizeof(asn_DEF_resourceType_tags_12)
		/sizeof(asn_DEF_resourceType_tags_12[0]), /* 2 */
	{ &asn_OER_type_resourceType_constr_12, &asn_PER_type_resourceType_constr_12, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_resourceType_specs_12	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_CSI_ResourceConfig_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CSI_ResourceConfig, csi_ResourceConfigId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CSI_ResourceConfigId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"csi-ResourceConfigId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CSI_ResourceConfig, csi_RS_ResourceSetList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_csi_RS_ResourceSetList_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"csi-RS-ResourceSetList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CSI_ResourceConfig, bwp_Id),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BWP_Id,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"bwp-Id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CSI_ResourceConfig, resourceType),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_resourceType_12,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"resourceType"
		},
};
static const ber_tlv_tag_t asn_DEF_CSI_ResourceConfig_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_CSI_ResourceConfig_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* csi-ResourceConfigId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* csi-RS-ResourceSetList */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* bwp-Id */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* resourceType */
};
asn_SEQUENCE_specifics_t asn_SPC_CSI_ResourceConfig_specs_1 = {
	sizeof(struct CSI_ResourceConfig),
	offsetof(struct CSI_ResourceConfig, _asn_ctx),
	asn_MAP_CSI_ResourceConfig_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	4,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_CSI_ResourceConfig = {
	"CSI-ResourceConfig",
	"CSI-ResourceConfig",
	&asn_OP_SEQUENCE,
	asn_DEF_CSI_ResourceConfig_tags_1,
	sizeof(asn_DEF_CSI_ResourceConfig_tags_1)
		/sizeof(asn_DEF_CSI_ResourceConfig_tags_1[0]), /* 1 */
	asn_DEF_CSI_ResourceConfig_tags_1,	/* Same as above */
	sizeof(asn_DEF_CSI_ResourceConfig_tags_1)
		/sizeof(asn_DEF_CSI_ResourceConfig_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_CSI_ResourceConfig_1,
	4,	/* Elements count */
	&asn_SPC_CSI_ResourceConfig_specs_1	/* Additional specs */
};

